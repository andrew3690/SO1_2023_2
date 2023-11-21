#include "fs.h"
#include <cmath>

int INE5412_FS::fs_format()
{
    if(mounted){
        cout << "Error: File system is already mounted! \n";
        return 0;
    }

    // formata o disco, apagando tudo nele
    const char formatted_data[4096] = {0};
    for (int block_id = 0; block_id < disk->size(); block_id++) {
        disk->write(block_id, formatted_data);
    }

    // Calculo da quantidade de blocos para inodes(10%)
    int inode_blocks = disk->size() * 0.1;

    // Criacao dos dados do bloco
    union fs_block block;

    // Escreve o superbloco
    block.super.magic = FS_MAGIC;
    block.super.nblocks = disk->size();
    block.super.ninodeblocks = inode_blocks;
    block.super.ninodes = INODES_PER_BLOCK * inode_blocks;

    disk->write(0, block.data);

    return 1;
}

void INE5412_FS::fs_debug()
{
    union fs_block block;
    disk->read(0, block.data);

    int nblocks = block.super.nblocks;  //numero de blocos ditado pelo superbloco

    cout << "superblock:\n";
    cout << "    " << (block.super.magic == FS_MAGIC ? "magic number is valid\n" : "magic number is invalid!\n");
    cout << "    " << block.super.nblocks << " blocks\n";
    cout << "    " << block.super.ninodeblocks << " inode blocks\n";
    cout << "    " << block.super.ninodes << " inodes\n";

    //itera os blocos de inodes
    for (int inode_block = 1; inode_block < block.super.ninodeblocks+1; inode_block++){
        disk->read(inode_block, block.data); // Carrega o bloco de inodes
        // Iterar pelos inodes
        for (int i = 0; i < INODES_PER_BLOCK; ++i) {

            // Calcula o índice dentro do bloco de inodes
            int inode_index = i % INODES_PER_BLOCK;

            // Verifica se o índice do inode é válido
            if (block.inode[inode_index].isvalid == 1) {
                cout << "inode " << i << ":\n";
                cout << "    size: " << block.inode[inode_index].size << " bytes\n";
                cout << "    direct blocks: ";

                // Iterar pelos ponteiros diretos do inode
                for (int j = 0; j < POINTERS_PER_INODE; ++j) {
                    // Verificar se o ponteiro direto aponta para um bloco válido
                    if (block.inode[inode_index].direct[j] > 0 && block.inode[inode_index].direct[j] < nblocks) {
                        cout << block.inode[inode_index].direct[j] << " ";
                    }
                }
                cout << "\n";

                // Verificar se o ponteiro indireto aponta para um bloco válido
                if (block.inode[inode_index].indirect > 0 && block.inode[inode_index].indirect < nblocks) {
                    cout << "    indirect block: " << block.inode[inode_index].indirect << "\n";
                    cout << "    indirect data blocks: ";
                    for (auto& pointer: find_indirect_blocks(block.inode[inode_index].indirect, nblocks)) {
                        cout << pointer << " ";
                    }
                }
                cout << "\n";
            }
        }
    }
}

/* Retorna um vetor com os indices dos blocos de dados apontados pelo bloco de ponteiros indiretos */
vector<int> INE5412_FS::find_indirect_blocks(int indirect_block, int nblocks)
{
    union fs_block indirect;
    vector<int> block_pointers;
    disk->read(indirect_block, indirect.data);
    for (int j = 0; j < POINTERS_PER_BLOCK; j++) {
        if (indirect.pointers[j] > 0 && indirect.pointers[j] < nblocks) {
            block_pointers.push_back(indirect.pointers[j]);
        }
    }
    return block_pointers;
}


int INE5412_FS::fs_mount() {
    if(mounted == true){
        return 0; // se a flag de montagem de arquivos for verdade, o sistema jah foi montado
    }

    // Ler o superbloco para obter informações sobre o sistema de arquivos
    union fs_block block;
    disk->read(0, block.data);

    // Verificar se o magic number é válido para confirmar a presença de um sistema de arquivos
    if (block.super.magic != FS_MAGIC) {
        // O magic number é inválido, indicando que não há sistema de arquivos formatado
        return 0; // Retornar zero para indicar falha na montagem do sistema de arquivos
    }

    number_of_blocks = block.super.nblocks;
    number_of_inode_blocks = block.super.ninodeblocks;

    // Inicializar o mapa de bits dos blocos livres/ocupados
    initialize_block_bitmap(block.super.nblocks, block.super.ninodeblocks);

    mounted = true;

    return 1; // Retornar um para indicar sucesso na montagem do sistema de arquivos
}

/* Responsável por varrer os inodes do disco na montagem e inicializar o bitmap de blocos livres,
observando quais os blocos utilizados por inodes*/
void INE5412_FS::initialize_block_bitmap(int nblocks, int ninodeblocks)
{
    // Determinar o número total de blocos no disco
    int total_blocks = disk->size();
    // Inicializar o vetor do mapa de bits com todos os blocos livres
    block_bitmap.resize(floor((total_blocks+31)/32), 0); // Inicializa todos os blocos como livres (0)

    // coloca o superbloco como ocupado
    set_block_as_used(0);

    union fs_block block;

    for (int inode_block = 1; inode_block < ninodeblocks+1; inode_block++) {
        disk->read(inode_block, block.data); // Carrega o bloco de inodes

        //seta os blocos reservados a inodes como ocupados
        set_block_as_used(inode_block);

        // Iterar pelos inodes
        for (int i = 0; i < INODES_PER_BLOCK; ++i) {

            // Calcula o índice dentro do bloco de inodes
            int inode_index = i % INODES_PER_BLOCK;

            // Verifica se o índice do inode é válido
            if (block.inode[inode_index].isvalid == 1) {

                set_block_as_used(block.inode[inode_index].indirect); //bloco indireto de ponteiros em uso

                // Iterar pelos ponteiros diretos do inode
                for (int j = 0; j < POINTERS_PER_INODE; ++j) {
                    if (block.inode[inode_index].direct[j] > 0 && block.inode[inode_index].direct[j] < nblocks) {
                        int direct_block = block.inode[inode_index].direct[j];
                        set_block_as_used(direct_block); //blocos diretos de dados em uso
                    }
                }

                // Verificar se o ponteiro indireto aponta para um bloco válido
                if (block.inode[inode_index].indirect > 0 && block.inode[inode_index].indirect < nblocks) {
                    for (auto& pointer: find_indirect_blocks(block.inode[inode_index].indirect, nblocks)) {
                        set_block_as_used(pointer); // blocos indiretos de dados em uso
                    }
                }
            }
        }
    }

    // //teste
    // for (int i = 0; i < total_blocks; ++i) {
    //     std::cout << "Block " << i << " is "
    //             << (block_is_free(i) ? "free" : "used")
    //             << std::endl;
    // }
}

void INE5412_FS::set_block_as_free(int block)
{
    int vector_index = block    /32;
    int position_bit_in_integer = block % 32;

    //seta o bit do block como 0 (livre)
    block_bitmap[vector_index] &= ~(1U << position_bit_in_integer);
}

void INE5412_FS::set_block_as_used(int block)
{
    int vector_index = block/32;
    int position_bit_in_integer = block % 32;

    //seta o bit do block como 1 (usado)
    block_bitmap[vector_index] |= (1U << position_bit_in_integer);
}

bool INE5412_FS::block_is_free(int block)
{
    int vector_index = block/32;
    int position_bit_in_integer = block % 32;

    //verifica se bloco é 0 (livre)
    return (block_bitmap[vector_index] & (1U << position_bit_in_integer)) == 0;
}

int INE5412_FS::fs_create() {
    if (!mounted) {
        return 0;
    }
    union fs_block block;

    // Encontrar um inode livre
    int inumber = find_free_inode(&block, number_of_inode_blocks);

    if(inumber == -1){
        //  Nao ha inodes livres disponiveis
        cout << "sem espaço para inodes disponivel\n";
        return 0;
    }

    // Marcar o inode como valido e com tamanho zero
    block.inode[inumber].isvalid = 1;
    block.inode[inumber].size = 0;

    // Escreve o bloco de inodes de volta no disco para salvar as alteracoes
    inode_save(inumber, block.inode[inumber]);

    // retorna o numero inode criado
    return inumber + 1;
    
}

int INE5412_FS::fs_delete(int inumber)
{
    if (!mounted) {
        cout << "Disco não está montado!\n";
        return 0;
    }
	fs_inode target_inode;
    inode_load(inumber, target_inode);

    cout << "entrei aqui !" << inumber << "\n";

    if(target_inode.isvalid != 1){
        return 0;
    }

    // liberacao dos blocos diretos
    for(int i = 0; i < POINTERS_PER_INODE; ++i){
        if (target_inode.direct[i] > 0){
            set_block_as_free(target_inode.direct[i]);
        }
    }

    // libera o bloco indireto se existir
    if(target_inode.indirect > 0){
        // le o bloco indireto
        set_block_as_free(target_inode.indirect); // bloco indireto de ponteiros liberado no bitmap

        // libera os blocos apontados pelo bloco indireto
        for(auto block: find_indirect_blocks(target_inode.indirect,number_of_blocks)){
            if(block != 0){
                set_block_as_free(block);
            }
        }
    }

    // marca o inode como invalido e retorna ao mapa de inodes livres
    target_inode.isvalid = 0;
    inode_save(inumber,target_inode);

    // //teste
    // for (int i = 0; i < 20; ++i) {
    //     std::cout << "Block " << i << " is "
    //             << (block_is_free(i) ? "free" : "used")
    //             << std::endl;
    // }

    return 1; // Sucesso na delecao do bloco

}

int INE5412_FS::fs_getsize(int inumber)
{
    if (!mounted) {
        cout << "disco não está montado!\n";
        return -1;
    }
    fs_inode target_inode;

    inode_load(inumber, target_inode);

    // verifica a validade do inode
    if(target_inode.isvalid != 1){
        // inode invalido, retorna falha
        return -1;
    }
    // retorna o tamanho do inode
    return target_inode.size;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
    if (!mounted) {
        cout << "disco não está montado!\n";
        return 0;
    }

    vector<char> inode_content;
    int read_bytes = 0;

    fs_inode inode;
    inode_load(inumber, inode); // carrega as informações do inode a partir do inumber
    if (inode.isvalid != 1) {
        return 0;
    }

    union fs_block block;

    // itera pelos blocos diretos do inode, e lê o conteudo
    for(auto& direct_ptr: inode.direct) {
        if (direct_ptr > 0) {
            disk->read(direct_ptr, block.data);
            for (auto& byte: block.data) {
                inode_content.push_back(byte);
            }
        }
    }

    // itera pelos ponteiros no bloco indireto do inode
    for (auto& data_block: find_indirect_blocks(inode.indirect, number_of_blocks)) {
        if (data_block > 0) {
            disk->read(data_block, block.data);
            for (auto& byte: block.data) {
                inode_content.push_back(byte);
            }
        }
    }

    //copia a partir do offset o conteudo do inode no buffer
    for (long unsigned int i = 0 + offset; i < inode_content.size(); i++) {
        if (read_bytes == 16384) {
            break;
        }
        read_bytes++;
        data[i-offset] = inode_content[i];
    }

	return read_bytes;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
    // Realiza leitura do inode
    fs_inode target_inode;
    disk->read(inumber / INODES_PER_BLOCK + 1,(char*)&target_inode);

    // verifica se o inode eh valido
    if (target_inode.isvalid != 1 || offset < 0){
        return 0; // inode ou deslocamento invalidos, retornando falha
    }

    int bytesw = 0; // contador de bytes escritos

    // calculo do numero de blocos necessarios com base no deslocamento e no comprimento do bloco
    int startBlock = offset / Disk::DISK_BLOCK_SIZE;
    int endblock = (offset + length) / Disk::DISK_BLOCK_SIZE;

    // loop que escreve em blocos diretos
    for(int i = startBlock; i <= endblock; ++i){
        // enquanto os contador estiver menor que a quantiodade de ponteiros por inode
        if(i < POINTERS_PER_INODE){
            // Aqui verifica se o bloco direto estah alocado
            if(target_inode.direct[i] == -1){
                // se sim aloca um novo bloco direto
                int newblock = find_free_block();
                if (newblock == -1){
                // se nao, que dizer que nao ha blocos livres, retornando o numero de bytes escritos ate o momento
                    return bytesw;
                }
                target_inode.direct[i] = newblock;
            }
            // Escreve os dados no bloco
            int blockOffset = offset % Disk::DISK_BLOCK_SIZE;
            int bytesToWrite = std::min(Disk::DISK_BLOCK_SIZE - blockOffset, length - bytesw);
            
            disk->write(target_inode.direct[i], data + bytesw);
            bytesw += bytesToWrite;
        } else {
            // Lógica para blocos indiretos, ainda tenho que pensar nessa parte
        }
    }

    // Atualiza o tamanho do inode, se necessário
    if (offset + bytesw > target_inode.size) {
        target_inode.size = offset + bytesw;
    }

    // Escreve o inode de volta no disco
    disk->write(inumber / INODES_PER_BLOCK + 1, (char*)&target_inode);

    return bytesw; // Retorna o número de bytes escritos
}

/* Encontra um lugar livre para adicionar inode */
int INE5412_FS::find_free_inode(fs_block *block, int ninodeblocks)
{
    int inumber = -1;
    for (int blocks = 1; blocks < ninodeblocks + 1; blocks++) {
        disk->read(blocks, block->data);
        for (int i = 0; i < INODES_PER_BLOCK; i++) {
            inumber++;
            int index = i % INODES_PER_BLOCK;
            if (block->inode[index].isvalid != 1) {
                return inumber;
            }
        }
    }
    return -1;
}

void INE5412_FS::inode_load(int inumber, fs_inode &inode)
{
    int disk_block = floor(inumber/INODES_PER_BLOCK) + 1;
    union fs_block block;

    disk->read(disk_block, block.data);
    inode = block.inode[inumber % INODES_PER_BLOCK];
}

void INE5412_FS::inode_save(int inumber, fs_inode inode)
{
    int disk_block = floor(inumber/INODES_PER_BLOCK) + 1;
    union fs_block block;

    disk->read(disk_block, block.data);
    block.inode[inumber % INODES_PER_BLOCK] = inode;
    disk->write(disk_block, block.data);

}

/* retorna primeiro bloco livre encontrado no bitmap */
int INE5412_FS::find_free_block() {
    // obtem o tamanho do disco
    int numBlocks = disk->size();

    // Verifica cada bloco no mapa de bits
    for (int block = 0; block < numBlocks; ++block) {
        // se um bloco está livre
        if (block_is_free(block)) {
            return block; 
        }
    }
    return -1; // Retorna -1 se não encontrar blocos livres
}
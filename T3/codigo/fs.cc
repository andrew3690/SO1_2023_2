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
    // for(int i = 0; i < inode_blocks; ++i){
    //     block.super.magic = FS_MAGIC;
    //     block.super.nblocks = disk->size();
    //     block.super.ninodeblocks = inode_blocks;
    //     block.super.ninodes = INODES_PER_BLOCK * i;

    //     disk->write(i + 1, block.data);
    // }

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
                    for (auto& pointer: find_indirect_blocks(block, inode_index, nblocks)) {
                        cout << pointer << " ";
                    }
                }
                cout << "\n";
            }
        }
    }
}

vector<int> INE5412_FS::find_indirect_blocks(fs_block block, int inode_index, int nblocks)
{
    union fs_block indirect;
    vector<int> block_pointers;
    disk->read(block.inode[inode_index].indirect, indirect.data);
    for (int j = 0; j < POINTERS_PER_BLOCK; j++) {
        if (indirect.pointers[j] > 0 && indirect.pointers[j] < nblocks) {
            block_pointers.push_back(indirect.pointers[j]);
        }
    }
    return block_pointers;
}


int INE5412_FS::fs_mount() {
    // Inserir aqui uma verificacao se o sistema de arquivos já está montado
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

    // Inicializar o mapa de bits dos blocos livres/ocupados
    initialize_block_bitmap(block.super.nblocks, block.super.ninodeblocks);

    mounted = true;
    
    return 1; // Retornar um para indicar sucesso na montagem do sistema de arquivos
}

void INE5412_FS::initialize_block_bitmap(int nblocks, int ninodeblocks)
{
    // Determinar o número total de blocos no disco
    int total_blocks = disk->size();
    // Inicializar o vetor do mapa de bits com todos os blocos livres
    block_bitmap.resize(total_blocks, 0); // Inicializa todos os blocos como livres (0)
    block_bitmap[0] = 1; // coloca o superbloco como ocupado

    union fs_block block;

    for (int inode_block = 1; inode_block < ninodeblocks+1; inode_block++) {
        disk->read(inode_block, block.data); // Carrega o bloco de inodes

        block_bitmap[inode_block] = 1;

        // Iterar pelos inodes
        for (int i = 0; i < INODES_PER_BLOCK; ++i) {

            // Calcula o índice dentro do bloco de inodes
            int inode_index = i % INODES_PER_BLOCK;

            // Verifica se o índice do inode é válido
            if (block.inode[inode_index].isvalid == 1) {

                block_bitmap[block.inode[inode_index].indirect] = 1; //bloco indireto de ponteiros em uso

                // Iterar pelos ponteiros diretos do inode
                for (int j = 0; j < POINTERS_PER_INODE; ++j) {
                    if (block.inode[inode_index].direct[j] > 0 && block.inode[inode_index].direct[j] < nblocks) {
                        int direct_block = block.inode[inode_index].direct[j];
                        block_bitmap[direct_block] = 1;
                    }
                }

                // Verificar se o ponteiro indireto aponta para um bloco válido
                if (block.inode[inode_index].indirect > 0 && block.inode[inode_index].indirect < nblocks) {
                    for (auto& pointer: find_indirect_blocks(block, inode_index, nblocks)) {
                        block_bitmap[pointer] = 1;
                    }
                }
            }
        }
    }
}

int INE5412_FS::fs_create()
{
    if (!mounted) {
        return 0;
    }
	// Realiza leitura do superbloco para obter informacoes sobre o sistema de arquivos
    union fs_block block;
    disk->read(0, block.data);

    // Encontrar um inode livre
    int inumber = find_free_inode(&block, block.super.ninodeblocks);

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

    //disk->write(inode_block_number(free_inode), block.data);

    // retorna o numero inode criado
    return inumber + 1;
    
}

int INE5412_FS::fs_delete(int inumber)
{
	// fs_inode target_inode;

    // disk->read(inumber / INODES_PER_BLOCK + 1, (char*)&target_inode);

    // if(target_inode.isvalid != 1){
    //     return 0;
    // }

    // // libreracao dos blocos diretos
    // for(int i = 0; i < POINTERS_PER_BLOCK; ++i){
    //     if(target_inode.direct[i] != -1){
    //     // Marca o bloco como livre
    //     free_blocks->set(target_inode.direct[i], false);
    //     }
    // }

    // // libera o bloco indireto se existir
    // if(target_inode.indirect != -1){
    //     // le o bloco indireto
    //     int indirect_block[POINTERS_PER_BLOCK];
    //     disk->read(target_inode.indirect, (char*)&indirect_block);

    //     // libera os blocos apontados pelo bloco indireto
    //     for(int i = 0; i < POINTERS_PER_BLOCK; ++i){
    //         if(indirect_block[i] != -1){
    //             free_blocks->set(indirect_block[i], false);
    //         }
    //     }

    //     // libera o bloco indireto
    //     free_blocks->set(target_inode.indirect, false);
    // }

    // // marca o inode como invalido e retorna ao mapa de inodes livres
    // target_inode.isvalid = 0;
    // disk->write(inumber/INODES_PER_BLOCK + 1, (char*)&target_inode);

    return 1; // Scesso na delecao do bloco

}

int INE5412_FS::fs_getsize(int inumber)
{
    fs_inode target_inode;

    // Realiza leitura do inode
    disk->read(inumber/ INODES_PER_BLOCK + 1, (char*)&target_inode);

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
        return 0;
    }
    vector<char> inode_content;
    int read_bytes = 0;

    fs_inode inode;
    inode_load(inumber, inode);
    if (inode.isvalid != 1) {
        return 0;
    }


    union fs_block block;
    for(auto& direct_ptr: inode.direct) {
        if (direct_ptr > 0) {
            disk->read(direct_ptr, block.data);
            for (auto& byte: block.data) {
                inode_content.push_back(byte);
            }
        }
    }
    for (long unsigned int i = 0 + offset; i < inode_content.size(); i++) {
        read_bytes++;
        data[i] = inode_content[i];
    }

	return read_bytes;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
	return 0;
}

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
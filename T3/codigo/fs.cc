#include "fs.h"

int INE5412_FS::fs_format()
{
    if(mounted){
        cout << "Error: File system is already mounted! \n";
        return 0;
    }

    // Calculo da quantidade de blocos para inodes(10%)
    int inode_blocks = disk->size() * 0.1;

    // Criacao dos dados do bloco
    union fs_block block;
    for(int i = 0; i < inode_blocks; ++i){
        block.super.magic = FS_MAGIC;
        block.super.nblocks = disk->size();
        block.super.ninodeblocks = inode_blocks;
        block.super.ninodes = INODES_PER_BLOCK * i;

        disk->write(i + 1, block.data);
    }

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
            if (block.inode[inode_index].isvalid) {
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
                    union fs_block indirect;
                    disk->read(block.inode[inode_index].indirect, indirect.data);
                    for (int j = 0; j < POINTERS_PER_BLOCK; j++) {
                        if (indirect.pointers[j] > 0 && indirect.pointers[j] < nblocks) {
                            cout << indirect.pointers[j] << " " ;
                        }
                    }
                }
                cout << "\n";
            }
        }
    }
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
        // O magic number é inválido, indicando que não há sistema de arquivos montado
        return 0; // Retornar zero para indicar falha na montagem do sistema de arquivos
    }

    // Inicializar o mapa de bits dos blocos livres/ocupados
    initialize_block_bitmap(block.super.nblocks);

    mounted = true;
    
    return 1; // Retornar um para indicar sucesso na montagem do sistema de arquivos
}

void INE5412_FS::initialize_block_bitmap(int nblocks)
{
    // Determinar o número total de blocos no disco
    int total_blocks = disk->size();
    // Inicializar o vetor do mapa de bits com todos os blocos livres
    block_bitmap.resize(total_blocks, 0); // Inicializa todos os blocos como livres (0)
}

int INE5412_FS::fs_create()
{
	return 0;
}

int INE5412_FS::fs_delete(int inumber)
{
	return 0;
}

int INE5412_FS::fs_getsize(int inumber)
{
	return -1;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
	return 0;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
	return 0;
}
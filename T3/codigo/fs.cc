#include "fs.h"

int INE5412_FS::fs_format()
{
	return 0;
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


int INE5412_FS::fs_mount()
{
	return 0;
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

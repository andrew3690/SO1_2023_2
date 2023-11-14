#include "fs.h"

int INE5412_FS::fs_format()
{
	return 0;
}

void INE5412_FS::fs_debug()
{
    union fs_block block;
    disk->read(0, block.data);

    cout << "superblock:\n";
    cout << "    " << (block.super.magic == FS_MAGIC ? "magic number is valid\n" : "magic number is invalid!\n");
    cout << "    " << block.super.nblocks << " blocks\n";
    cout << "    " << block.super.ninodeblocks << " inode blocks\n";
    cout << "    " << block.super.ninodes << " inodes\n";

    // Iterar pelos inodes
    for (int i = 0; i < block.super.ninodes; ++i) {
        disk->read(i / INODES_PER_BLOCK + 1, block.data); // Carrega o bloco de inodes

        // Calcula o índice dentro do bloco de inodes
        int inode_index = i % INODES_PER_BLOCK;

        // Verifica se o índice do inode é válido
        if (block.inode[inode_index].isvalid) {
            cout << "inode " << i << ":\n";
            cout << "    size: " << block.inode[inode_index].size << " bytes\n";
            cout << "    direct blocks:\n";

            // Iterar pelos ponteiros diretos do inode
            for (int j = 0; j < POINTERS_PER_INODE; ++j) {
                // Verificar se o ponteiro direto aponta para um bloco válido
                if (block.inode[inode_index].direct[j] >= 0 && block.inode[inode_index].direct[j] < block.super.nblocks) {
                    cout << "        " << block.inode[inode_index].direct[j] << "\n";
                }
            }

            // Verificar se o ponteiro indireto aponta para um bloco válido
            if (block.inode[inode_index].indirect >= 0 && block.inode[inode_index].indirect < block.super.nblocks) {
                cout << "    indirect block: " << block.inode[inode_index].indirect << "\n";
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

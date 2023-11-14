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

    for (int i = 0; i < block.super.ninodes; ++i) {
        fs_inode current_inode = block.inode[i];

        // Verificar se o inode está em uso
        if (current_inode.isvalid) {
            cout << "inode " << i << ":\n";
            cout << "    size: " << current_inode.size << " bytes\n";
            cout << "    direct blocks: ";
            for (int j = 0; j < POINTERS_PER_INODE; ++j) {
                cout << current_inode.direct[j] << " ";
            }
            cout << "\n";

            // Verificar se há um bloco indireto
            if (current_inode.indirect) {
                cout << "    indirect block: " << current_inode.indirect << "\n";
                
                // Lógica para ler o bloco indireto
                union fs_block indirect_block;
				
                disk->read(current_inode.indirect, indirect_block.data);

                // Exibir os ponteiros para os blocos de dados
                cout << "    indirect block pointers: ";
                for (int k = 0; k < disk->size(); ++k) {
                    cout << indirect_block.pointers[k] << " ";
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

#ifndef FS_H
#define FS_H

#include "disk.h"
#include <vector>
class INE5412_FS
{
public:
    static const unsigned int FS_MAGIC = 0xf0f03410;
    static const unsigned short int INODES_PER_BLOCK = 128;
    static const unsigned short int POINTERS_PER_INODE = 5;
    static const unsigned short int POINTERS_PER_BLOCK = 1024;

    class fs_superblock {
        public:
            unsigned int magic;
            int nblocks;
            int ninodeblocks;
            int ninodes;
    }; 

    class fs_inode {
        public:
            int isvalid;
            int size;
            int direct[POINTERS_PER_INODE];
            int indirect;
    };

    union fs_block {
        public:
            fs_superblock super;
            fs_inode inode[INODES_PER_BLOCK];
            int pointers[POINTERS_PER_BLOCK];
            char data[Disk::DISK_BLOCK_SIZE];
    };

    // Classe de blocos livres
    class Freeblocks {
    private:
        std::vector<bool> blockMap; // Vetor de booleanos para representar blocos livres

    public:
        Freeblocks(int nblocks) : blockMap(nblocks, true) {} // Inicializa todos os blocos

        // Marca o bloco como livre
        void set(int blockNum, bool freeStatus) {
            blockMap[blockNum] = freeStatus;
        }

        // Verifica se o bloco está livre
        bool isFree(int blockNum) {
            return blockMap[blockNum];
        }

        // Obtém o estado de um bloco específico
        bool get(int blockNum) {
            if (blockNum < 0 || blockNum >= blockMap.size()) {
                // Caso o bloco solicitado seja inválido, retorna false ou uma flag indicando erro
                // Aqui, estou retornando false para indicar que o bloco está ocupado ou inválido
                return false;
            }
            return blockMap[blockNum];
        }
    };


public:

    INE5412_FS(Disk *d) {
        disk = d;
    } 

    void fs_debug();
    int  fs_format();
    int  fs_mount();

    int  fs_create();
    int  fs_delete(int inumber);
    int  fs_getsize(int inumber);

    int  fs_read(int inumber, char *data, int length, int offset);
    int  fs_write(int inumber, const char *data, int length, int offset);
    void inode_load(int inumber, fs_inode &inode);
    void inode_save(int inumber, fs_inode inode);
    int find_free_inode(fs_block *block, int ninodeblocks);
    vector<int> find_indirect_blocks(int indirect_block, int nblocks);

private:
    Disk *disk;
    Freeblocks *free_blocks;
    bool mounted = false;

    // vetor de mapa de bits
    std::vector<int> block_bitmap;

    // metodo de incializacao do mapa de bits
    void initialize_block_bitmap(int nblocks, int ninodeblocks);
    
    //metdo que acha os blocos indiretos
    // vector<int> find_indirect_blocks(fs_block block, int index, int n_of_blocks);
    
    // metodo que acha os inodes livres
    // int find_free_inode(union fs_block& block);
    
    // metedo de obtencao do numero do bloco do inode
    int inode_block_number(int number);
    int find_free_block();

};

#endif
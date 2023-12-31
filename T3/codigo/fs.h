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

public:

    INE5412_FS(Disk *d) {
        disk = d;
    } 

    void fs_debug(); // ok
    int  fs_format(); // ok
    int  fs_mount(); // ok

    int  fs_create(); // ok
    int  fs_delete(int inumber); // ok
    int  fs_getsize(int inumber); // ok

    int  fs_read(int inumber, char *data, int length, int offset); // ok
    int  fs_write(int inumber, const char *data, int length, int offset); // ok
    
    // metodos que criamos
    void inode_load(int inumber, fs_inode &inode);
    void inode_save(int inumber, fs_inode inode);
    int find_free_inode(fs_block *block, int ninodeblocks);
    vector<int> find_indirect_blocks(int indirect_block, int nblocks);

    // métodos para o bitmap de blocos livres
    void set_block_as_free(int block_index);
    void set_block_as_used(int block_index);
    bool block_is_free(int block_index);

private:
    Disk *disk;
    bool mounted = false;
    int number_of_blocks = 0;
    int number_of_inode_blocks = 0;

    // vetor de mapa de bits
    std::vector<uint32_t> block_bitmap;

    // metodo de incializacao do mapa de bits
    void initialize_block_bitmap(int nblocks, int ninodeblocks);

    int find_free_block();

};

#endif
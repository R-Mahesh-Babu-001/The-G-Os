#ifndef THE_G_OS_VFS_HPP
#define THE_G_OS_VFS_HPP

#define VFS_MAX_NODES 32
#define VFS_MAX_NAME  32
#define VFS_MAX_DATA  512
#define VFS_MAX_CHILDREN 8

enum VfsNodeType {
    VFS_FILE,
    VFS_DIR
};

struct VfsNode {
    int used;
    int parent;
    VfsNodeType type;
    char name[VFS_MAX_NAME];
    char data[VFS_MAX_DATA];
    int size;
    int children[VFS_MAX_CHILDREN];
    int child_count;
};

void vfs_init();
void vfs_ls();
void vfs_pwd();
void vfs_tree();
void vfs_cat(const char* name);
void vfs_touch(const char* name);
void vfs_mkdir(const char* name);
void vfs_write(const char* name, const char* data);
void vfs_cd(const char* name);

#endif
#ifndef THE_G_OS_RAMFS_HPP
#define THE_G_OS_RAMFS_HPP

struct RamFile {
    const char* name;
    const char* content;
};

void ramfs_list();
void ramfs_cat(const char* filename);

#endif
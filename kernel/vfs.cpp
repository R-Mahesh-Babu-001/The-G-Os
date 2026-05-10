#include "vfs.hpp"
#include "terminal.hpp"
#include "string.hpp"

static VfsNode nodes[VFS_MAX_NODES];
static int current_dir = 0;

static int alloc_node() {
    for (int i = 0; i < VFS_MAX_NODES; i++) {
        if (!nodes[i].used) {
            nodes[i].used = 1;
            nodes[i].child_count = 0;
            nodes[i].size = 0;
            return i;
        }
    }
    return -1;
}

static int find_child(int dir, const char* name) {
    for (int i = 0; i < nodes[dir].child_count; i++) {
        int child = nodes[dir].children[i];

        if (kstrcmp(nodes[child].name, name)) {
            return child;
        }
    }

    return -1;
}

static void add_child(int parent, int child) {
    if (nodes[parent].child_count >= VFS_MAX_CHILDREN) {
        terminal_print_color("Directory full.\n", COLOR_RED);
        return;
    }

    nodes[parent].children[nodes[parent].child_count++] = child;
    nodes[child].parent = parent;
}

static void print_path_recursive(int node) {
    if (node == 0) {
        terminal_print("/");
        return;
    }

    print_path_recursive(nodes[node].parent);
    terminal_print(nodes[node].name);
    terminal_print("/");
}

static void tree_recursive(int node, int depth) {
    for (int i = 0; i < depth; i++) {
        terminal_print("  ");
    }

    if (nodes[node].type == VFS_DIR) {
        terminal_print("[DIR] ");
    } else {
        terminal_print("[FILE] ");
    }

    terminal_print(nodes[node].name);
    terminal_print("\n");

    if (nodes[node].type == VFS_DIR) {
        for (int i = 0; i < nodes[node].child_count; i++) {
            tree_recursive(nodes[node].children[i], depth + 1);
        }
    }
}

void vfs_init() {
    for (int i = 0; i < VFS_MAX_NODES; i++) {
        nodes[i].used = 0;
        nodes[i].child_count = 0;
        nodes[i].size = 0;
    }

    int root = alloc_node();
    nodes[root].type = VFS_DIR;
    nodes[root].parent = root;
    kstrcpy(nodes[root].name, "");

    current_dir = root;

    vfs_mkdir("system");
    vfs_mkdir("home");

    vfs_touch("readme");
    vfs_write("readme", "Welcome to The-G-Os RAM VFS.\nThis file system is stored inside kernel memory.\n");

    vfs_cd("system");
    vfs_touch("info");
    vfs_write("info", "The-G-Os v0.4 RAM File System\nDSA used: tree, inode table, static arrays, allocation map.\n");
    vfs_cd("..");
}

void vfs_ls() {
    VfsNode* dir = &nodes[current_dir];

    for (int i = 0; i < dir->child_count; i++) {
        int child = dir->children[i];

        if (nodes[child].type == VFS_DIR) {
            terminal_print_color("[DIR]  ", COLOR_CYAN);
        } else {
            terminal_print_color("[FILE] ", COLOR_GREEN);
        }

        terminal_print(nodes[child].name);
        terminal_print("\n");
    }
}

void vfs_pwd() {
    print_path_recursive(current_dir);
    terminal_print("\n");
}

void vfs_tree() {
    tree_recursive(0, 0);
}

void vfs_cat(const char* name) {
    int node = find_child(current_dir, name);

    if (node == -1) {
        terminal_print_color("File not found.\n", COLOR_RED);
        return;
    }

    if (nodes[node].type != VFS_FILE) {
        terminal_print_color("Not a file.\n", COLOR_RED);
        return;
    }

    terminal_print(nodes[node].data);
}

void vfs_touch(const char* name) {
    if (!name || name[0] == '\0') {
        terminal_print_color("Usage: touch filename\n", COLOR_YELLOW);
        return;
    }

    if (find_child(current_dir, name) != -1) {
        terminal_print_color("File already exists.\n", COLOR_RED);
        return;
    }

    int node = alloc_node();

    if (node == -1) {
        terminal_print_color("No free VFS nodes.\n", COLOR_RED);
        return;
    }

    nodes[node].type = VFS_FILE;
    kstrncpy(nodes[node].name, name, VFS_MAX_NAME);
    nodes[node].data[0] = '\0';
    nodes[node].size = 0;

    add_child(current_dir, node);
}

void vfs_mkdir(const char* name) {
    if (!name || name[0] == '\0') {
        terminal_print_color("Usage: mkdir dirname\n", COLOR_YELLOW);
        return;
    }

    if (find_child(current_dir, name) != -1) {
        terminal_print_color("Directory already exists.\n", COLOR_RED);
        return;
    }

    int node = alloc_node();

    if (node == -1) {
        terminal_print_color("No free VFS nodes.\n", COLOR_RED);
        return;
    }

    nodes[node].type = VFS_DIR;
    kstrncpy(nodes[node].name, name, VFS_MAX_NAME);

    add_child(current_dir, node);
}

void vfs_write(const char* name, const char* data) {
    int node = find_child(current_dir, name);

    if (node == -1) {
        vfs_touch(name);
        node = find_child(current_dir, name);
    }

    if (node == -1 || nodes[node].type != VFS_FILE) {
        terminal_print_color("Cannot write file.\n", COLOR_RED);
        return;
    }

    kstrncpy(nodes[node].data, data, VFS_MAX_DATA);
    nodes[node].size = kstrlen(nodes[node].data);
}

void vfs_cd(const char* name) {
    if (!name || name[0] == '\0') {
        current_dir = 0;
        return;
    }

    if (kstrcmp(name, "/")) {
        current_dir = 0;
        return;
    }

    if (kstrcmp(name, "..")) {
        current_dir = nodes[current_dir].parent;
        return;
    }

    int node = find_child(current_dir, name);

    if (node == -1) {
        terminal_print_color("Directory not found.\n", COLOR_RED);
        return;
    }

    if (nodes[node].type != VFS_DIR) {
        terminal_print_color("Not a directory.\n", COLOR_RED);
        return;
    }

    current_dir = node;
}
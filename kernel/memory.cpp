#include "memory.hpp"
#include "terminal.hpp"

#define TOTAL_MEMORY_MB 512
#define PAGE_SIZE 4096
#define TOTAL_PAGES ((TOTAL_MEMORY_MB * 1024 * 1024) / PAGE_SIZE)
#define BITMAP_SIZE (TOTAL_PAGES / 8)

static unsigned char page_bitmap[BITMAP_SIZE];

static void bitmap_set(int index) {
    page_bitmap[index / 8] |= (1 << (index % 8));
}

static int bitmap_get(int index) {
    return page_bitmap[index / 8] & (1 << (index % 8));
}

void memory_init() {
    for (int i = 0; i < BITMAP_SIZE; i++) {
        page_bitmap[i] = 0;
    }

    for (int i = 0; i < 256; i++) {
        bitmap_set(i);
    }
}

void memory_info() {
    int used = 0;

    for (int i = 0; i < TOTAL_PAGES; i++) {
        if (bitmap_get(i)) {
            used++;
        }
    }

    int free_pages = TOTAL_PAGES - used;

    terminal_print("Memory Manager: Bitmap Page Allocator Skeleton\n");
    terminal_print("Assumed RAM: ");
    terminal_print_dec(TOTAL_MEMORY_MB);
    terminal_print(" MB\n");

    terminal_print("Page Size: ");
    terminal_print_dec(PAGE_SIZE);
    terminal_print(" bytes\n");

    terminal_print("Total Pages: ");
    terminal_print_dec(TOTAL_PAGES);
    terminal_print("\n");

    terminal_print("Used Pages: ");
    terminal_print_dec(used);
    terminal_print("\n");

    terminal_print("Free Pages: ");
    terminal_print_dec(free_pages);
    terminal_print("\n");

    terminal_print("Status: Ready for real boot memory-map integration.\n");
}
#include "pci.hpp"
#include "io.hpp"
#include "terminal.hpp"

static void outl(unsigned short port, unsigned int value) {
    asm volatile("outl %0, %1" : : "a"(value), "Nd"(port));
}

static unsigned int inl(unsigned short port) {
    unsigned int result;
    asm volatile("inl %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

static unsigned int pci_config_read(unsigned char bus, unsigned char slot, unsigned char func, unsigned char offset) {
    unsigned int address;

    address = ((unsigned int)bus << 16)
            | ((unsigned int)slot << 11)
            | ((unsigned int)func << 8)
            | (offset & 0xFC)
            | 0x80000000;

    outl(0xCF8, address);

    return inl(0xCFC);
}

static unsigned short pci_vendor_id(unsigned char bus, unsigned char slot, unsigned char func) {
    return pci_config_read(bus, slot, func, 0x00) & 0xFFFF;
}

static unsigned short pci_device_id(unsigned char bus, unsigned char slot, unsigned char func) {
    return (pci_config_read(bus, slot, func, 0x00) >> 16) & 0xFFFF;
}

static unsigned char pci_class_code(unsigned char bus, unsigned char slot, unsigned char func) {
    return (pci_config_read(bus, slot, func, 0x08) >> 24) & 0xFF;
}

static unsigned char pci_subclass(unsigned char bus, unsigned char slot, unsigned char func) {
    return (pci_config_read(bus, slot, func, 0x08) >> 16) & 0xFF;
}

void pci_scan() {
    terminal_print("Scanning PCI devices...\n");

    int found = 0;

    for (unsigned int bus = 0; bus < 256; bus++) {
        for (unsigned int slot = 0; slot < 32; slot++) {
            unsigned short vendor = pci_vendor_id(bus, slot, 0);

            if (vendor != 0xFFFF) {
                unsigned short device = pci_device_id(bus, slot, 0);
                unsigned char class_code = pci_class_code(bus, slot, 0);
                unsigned char subclass = pci_subclass(bus, slot, 0);

                terminal_print("PCI Device -> Bus ");
                terminal_print_dec(bus);
                terminal_print(", Slot ");
                terminal_print_dec(slot);
                terminal_print(" | Vendor ");
                terminal_print_hex(vendor);
                terminal_print(" | Device ");
                terminal_print_hex(device);
                terminal_print(" | Class ");
                terminal_print_hex(class_code);
                terminal_print(" | Subclass ");
                terminal_print_hex(subclass);
                terminal_print("\n");

                found++;
            }
        }
    }

    if (found == 0) {
        terminal_print("No PCI devices detected.\n");
    } else {
        terminal_print("PCI scan complete. Devices found: ");
        terminal_print_dec(found);
        terminal_print("\n");
    }
}
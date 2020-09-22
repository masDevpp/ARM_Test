#include "Startup.h"

void Startup::Run() {
    LoadMemory();
}

void Startup::LoadMemory() {
    extern char _data_load_source[];
    extern char _data_load_size[];
    extern char _data_load_destinatin[];
    extern char _bss_address[];
    extern char _bss_size[];

    // Load data section from ROM to RAM
    int32 size = (uint64)_data_load_size;
    for (int i = 0; i < size; i++) {
        _data_load_destinatin[i] = _data_load_source[i];
    }

    // Zero clear bss section
    size = (uint64)_bss_size;
    for (int i = 0; i < size; i++) {
        _bss_address[i] = 0;
    }
}
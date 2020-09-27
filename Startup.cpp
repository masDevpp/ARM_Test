#include "Startup.h"

void Startup::Run() {
    // Enable FPU by coprocessor access control register
    uint32 *cpacr = (uint32 *)0xE000ED88;
    *cpacr = 0x00F00000;

    LoadMemory();
    RCCSetup();
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

void Startup::RCCSetup() {
    *((uint32 *)RCC_AHB1ENR) |= RCC_AHB1ENR_GPIOAEN_MASK;
    *((uint32 *)RCC_APB1ENR) |= RCC_APB1ENA_APB1ENR_MASK | RCC_APB1ENA_USART2EN_MASK;
}
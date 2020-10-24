#include "Startup.h"
#include "Memory.h"
#include "Trace.h"
#include "Timer.h"

volatile RCC_AHB1ENR_reg *Startup::RCC_AHB1ENR = (RCC_AHB1ENR_reg *)(RCC + 0x30);
volatile RCC_APB1ENR_reg *Startup::RCC_APB1ENR = (RCC_APB1ENR_reg *)(RCC + 0x40);
volatile RCC_APB2ENR_reg *Startup::RCC_APB2ENR = (RCC_APB2ENR_reg *)(RCC + 0x44);

void Startup::Run() {
    // Enable FPU by coprocessor access control register
    uint32 *cpacr = (uint32 *)0xE000ED88;
    *cpacr = 0x00F00000;

    LoadMemory();

    Memory::Setup();

    RCCSetup();

    Trace::Setup();
    TimerProvider::Setup();
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
    RCC_AHB1ENR->GPIOAEN  = true;

    RCC_APB1ENR->TIM13EN  = true;
    RCC_APB1ENR->TIM14EN  = true;

    RCC_APB1ENR->USART2EN = true;

    RCC_APB2ENR->TIM10EN   = true;
    RCC_APB2ENR->TIM11EN   = true;
}
#include "Kernel.h"
#include "SystemRegister.hh"
#include "LEDHandler.h"
#include "CommandHandler.h"
#include "Startup.h"
#include "Memory.h"

extern char _stack_bottom[];
extern char _stack_size[];

extern "C" void _setup_thread_stack(uint32 pc, uint32 sp, uint32 numContextRegister);
extern "C" void _start_thread(uint32 pc, uint32 sp);
extern "C" void _thread_switch(uint32 currentSPAddr, uint32 nextSP, uint32 lr);

uint32 Kernel::CurrentThread;
uint32 Kernel::NextThread;

uint32 *Kernel::KernelSP;
uint32 *Kernel::ThreadSP;
uint32 *Kernel::CurrentThreadSP;
uint32 *Kernel::NextThreadSP;
uint32 Kernel::NumberOfThreads = NumOfThreads;

void Kernel::Setup() {
    Startup::Run();
    
    uint32 firstThreadPC;
    uint32 firstThreadSP;
    SetupThread(firstThreadPC, firstThreadSP);

    // Setup SysTick
    volatile SYST_CSR_reg *SYST_CSR = (SYST_CSR_reg *)0xE000E010;
    volatile SYST_RVR_reg *SYST_RVR = (SYST_RVR_reg *)0xE000E014;
    volatile SYST_CVR_reg *SYST_CVR = (SYST_CVR_reg *)0xE000E018;

    SYST_RVR->RELOAD = 0x000000ff;
    SYST_CVR->CURRENT = 0x000000ff;
    SYST_CSR->TICKINT = true;
    SYST_CSR->ENABLE = true;

    // Execute first thread
    _start_thread(firstThreadPC, firstThreadSP);
}

void Kernel::SetupThread(uint32 &firstThreadPC, uint32 &firstThreadSP) {
    ThreadSP = (uint32 *)Memory::Allocate(sizeof(uint32) * NumOfThreads);
    
    uint32 stackBottom = (uint32)_stack_bottom;
    uint32 totalStackSize = (uint32)_stack_size;
    uint32 threadStackSize = ((totalStackSize - (0x10 * NumOfThreads)) / NumOfThreads) & 0xfffffffc;

    // Nothing to do for kernel thread (Threads[Kernel]) but just update stack pointer
    uint32 currentStackPointer = stackBottom - threadStackSize;
    
    // LEDHandler thread
    uint32 pc = (uint32)LEDHandler::Setup;
    uint32 sp = currentStackPointer - ((NUM_CONTEXT_REGISTER + NUM_CPU_SAVE_REGISTER) * 4);
    firstThreadPC = pc;
    firstThreadSP = currentStackPointer;

    ThreadSP[LEDHandlerThread] = sp;

    _setup_thread_stack(pc, sp, NUM_CONTEXT_REGISTER + NUM_CPU_SAVE_REGISTER);
    currentStackPointer -= threadStackSize;

    // CommandHandler thead
    pc = (uint32)CommandHandler::Setup;
    sp = currentStackPointer - ((NUM_CONTEXT_REGISTER + NUM_CPU_SAVE_REGISTER) * 4);

    ThreadSP[CommandHandlerThread] = sp;

    _setup_thread_stack(pc, sp, NUM_CONTEXT_REGISTER + NUM_CPU_SAVE_REGISTER);
    currentStackPointer -= threadStackSize;
    
    CurrentThread = LEDHandlerThread;
    NextThread = CommandHandlerThread;
}

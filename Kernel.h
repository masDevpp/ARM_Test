#include "DataType.h"

const uint32 NUM_CONTEXT_REGISTER = 8; // r0-r7 stored by OS
const uint32 NUM_CPU_SAVE_REGISTER = 8; // r0-r3, r12, lr, pc and xpsr, these are stored by CPU

enum ThreadEnum {
    LEDHandlerThread,
    CommandHandlerThread,
    NumOfThreads,
};

class Thread {
public:
    void (*PC)();
    uint32 SP;
};

class Kernel {
public:
    static void Setup();
    static void SetupThread();

    static uint32 SysTickInterrupt(uint32 lr);

    static Thread *Threads;//[NumOfThreads];

    static uint32 NumberOfThreads;

    static uint32 *KernelSP;
    static uint32 *ThreadSP;
    static uint32 *CurrentThreadSP;
    static uint32 *NextThreadSP;
    static uint32 CurrentThread;
    static uint32 NextThread;

};

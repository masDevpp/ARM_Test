#include "DataType.h"

class Startup {
public:
    static void Run();

private:
    static void LoadMemory();
    static void RCCSetup();

    // RCC
    static const uint32 RCC          = 0x40023800;

    // AHB1 for GPIO
    static const uint32 RCC_AHB1ENR  = RCC + 0x30;
    static const uint32 RCC_AHB1ENR_GPIOAEN_MASK = 0x00000001;

    // APB1 for Timer
    static const uint32 RCC_APB1ENR  = RCC + 0x40;
    static const uint32 RCC_APB1ENA_APB1ENR_MASK = 0x00000001;
    static const uint32 RCC_APB1ENA_USART2EN_MASK = 0x00020000;
};
#include "DataType.h"

class LEDManager {
public:
    static void SetupLED();
    static void SetLED(bool isOn);

private:
    // GPIOA
    static const uint32 GPIOA        = 0x40020000;
    static const uint32 GPIOA_MODER  = GPIOA + 0x00;
    static const uint32 GPIOA_OTYPER = GPIOA + 0x04;
    static const uint32 GPIOA_ODR    = GPIOA + 0x14;
    static const uint32 GPIOA_BSRR   = GPIOA + 0x18;

    static const uint32 GPIOA_MODER_PA5_OUTPUT_MODE_MASK = 0x00000400;
    static const uint32 GPIOA_ODR_PA5_MASK = 0x00000020;
    static const uint32 GPIOA_BSRR_PA5_SET_MASK = 0x00000020;
    static const uint32 GPIOA_BSRR_PA5_RESET_MASK = 0x00200000;

    // RCC
    static const uint32 RCC          = 0x40023800;
    static const uint32 RCC_AHB1ENR  = RCC + 0x30;

    static const uint32 RCC_AHB1ENR_GPIOAEN_MASK = 0x00000001;
};
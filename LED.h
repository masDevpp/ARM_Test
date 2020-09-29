#include "DataType.h"
#include "GPIO.hh"

class LEDManager {
public:
    LEDManager();
    void SetLED(bool isOn);

private:
    // GPIOA
    const uint32 GPIOA = 0x40020000;
    volatile GPIO_MODER *GPIOA_MODER = (GPIO_MODER *)(GPIOA + 0x00);
    volatile GPIO_BSRR  *GPIOA_BSRR  = (GPIO_BSRR  *)(GPIOA + 0x18);
};

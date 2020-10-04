#include "DataType.h"
#include "GPIO.hh"

class LEDManager {
public:
    static void Setup();
    static void SetLED(bool isOn);
    static bool GetLED();

private:
    // GPIOA
    static const uint32 GPIOA = 0x40020000;
    static volatile GPIO_MODER *GPIOA_MODER;
    static volatile GPIO_ODR   *GPIOA_ODR;
    static volatile GPIO_BSRR  *GPIOA_BSRR;
};

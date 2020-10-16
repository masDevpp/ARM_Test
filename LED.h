#pragma once
#include "DataType.h"
#include "GPIO.hh"

class LED {
public:
    static void Setup();
    static void Set(bool isOn);
    static bool Get();

private:
    // GPIOA
    static const uint32 GPIOA = 0x40020000;
    static volatile GPIO_MODER *GPIOA_MODER;
    static volatile GPIO_ODR   *GPIOA_ODR;
    static volatile GPIO_BSRR  *GPIOA_BSRR;
};

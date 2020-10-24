#pragma once
#include "DataType.h"
#include "RCC.hh"

class Startup {
public:
    static void Run();

private:
    static void LoadMemory();
    static void RCCSetup();

    static const uint32 RCC = 0x40023800;
    static volatile RCC_AHB1ENR_reg *RCC_AHB1ENR;
    static volatile RCC_APB1ENR_reg *RCC_APB1ENR;
    static volatile RCC_APB2ENR_reg *RCC_APB2ENR;
};
#pragma once
#include "DataType.h"

class Timer {
public:
    uint32 Setup(uint16 preScaler = 0, uint32 autoReload = 0xffffffff);
    void Start();
    void Stop();
    uint32 GetElapseMs();

private:
    uint16 PreScaler;
    uint32 AutoReload;

    uint32 HSIClock = 16 * 1000 * 1000; // 16MHz

    uint32 *TIM2 = (uint32 *)0x40000000;
    uint32 *TIM2_CR1 = TIM2 + 0x00 / 4;
    uint32 *TIM2_EGR = TIM2 + 0x14 / 4;
    uint32 *TIM2_CNT = TIM2 + 0x24 / 4;
    uint32 *TIM2_PSC = TIM2 + 0x28 / 4;
    uint32 *TIM2_ARR = TIM2 + 0x2C / 4;

    uint32 TIM2_CR1_CEN_MASK = 0x00000001;
    uint32 TIM2_EGR_UG_MASK  = 0x00000001;
};

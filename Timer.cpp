#include "Timer.h"

uint32 Timer::Setup(uint16 preScaler, uint32 autoReload) {
    PreScaler = preScaler;
    AutoReload = autoReload;

    // Stop counter
    *TIM2_CR1 &= ~TIM2_CR1_CEN_MASK;

    // Load register
    *TIM2_PSC = (uint32)preScaler;
    *TIM2_ARR = autoReload;

    // Apply change
    *TIM2_EGR |= TIM2_EGR_UG_MASK;

    // Return max countable milli sec
    return AutoReload / (PreScaler + 1) / (HSIClock / 1000);
}

void Timer::Start() {
    *TIM2_CR1 |= TIM2_CR1_CEN_MASK;
}

void Timer::Stop() {
    *TIM2_CR1 &= ~TIM2_CR1_CEN_MASK;
}

uint32 Timer::GetElapseMs() {
    uint32 currentCount = *TIM2_CNT;

    return currentCount / (PreScaler + 1) / (HSIClock / 1000);
}
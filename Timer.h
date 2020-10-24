#pragma once
#include "Timer.hh"

class Timer {
public:
    void Initialize(uint32 baseAddress);
    uint32 Setup(uint16 preScaler = 0x1000, uint16 autoReload = 0xffff);
    void Start();
    void Stop();
    void Reset();
    uint32 GetElapseMs();

    uint32 BaseAddress;
    uint16 PreScaler;
    uint16 AutoReload;

private:
    static const uint32 HSI_CLOCK = 16 * 1000 * 1000; // 16MHz

    volatile TIM_CR1_reg   *TIM_CR1;
    volatile TIM_DIER_reg  *TIM_DIER;
    volatile TIM_SR_reg    *TIM_SR;
    volatile TIM_EGR_reg   *TIM_EGR;
    volatile TIM_CCMR1_reg *TIM_CCMR1;
    volatile TIM_CCER_reg  *TIM_CCER;
    volatile TIM_CNT_reg   *TIM_CNT;
    volatile TIM_PSC_reg   *TIM_PSC;
    volatile TIM_ARR_reg   *TIM_ARR;

    static const uint32 TIM_CR1_OFFSET   = 0x00;
    static const uint32 TIM_DIER_OFFSET  = 0x0c;
    static const uint32 TIM_SR_OFFSET    = 0x10;
    static const uint32 TIM_EGR_OFFSET   = 0x14;
    static const uint32 TIM_CCMR1_OFFSET = 0x18;
    static const uint32 TIM_CCER_OFFSET  = 0x20;
    static const uint32 TIM_CNT_OFFSET   = 0x24;
    static const uint32 TIM_PSC_OFFSET   = 0x28;
    static const uint32 TIM_ARR_OFFSET   = 0x2c;
};

// TimerProvider provide available Timer class instance from Timers[]
class TimerProvider {
public:
    static void Setup();
    static Timer *GetInstance();
    static void Release(Timer timer);

private:
    static const uint32 NUM_TIMER = 4;

    static const uint32 TIMER_ADDRESS[NUM_TIMER];
    static bool TimerUsed[NUM_TIMER];
    static Timer Timers[NUM_TIMER];
};
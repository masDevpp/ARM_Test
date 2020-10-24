#include "Timer.h"
#include "Kernel.h"

const uint32 TimerProvider::TIMER_ADDRESS[] = {0x40014400, 0x40014800, 0x40001C00, 0x40002000};
bool TimerProvider::TimerUsed[];
Timer TimerProvider::Timers[];

void TimerProvider::Setup() {
    for (uint32 i = 0; i < NUM_TIMER; i++) {
        Timers[i].Initialize(TIMER_ADDRESS[i]);
        TimerUsed[i] = false;
    }
}

Timer *TimerProvider::GetInstance() {
    uint32 found = false;

    Timer *timer;

    for (uint32 i = 0; i < NUM_TIMER; i++) {
        if (!TimerUsed[i]) {
            found = true;
            TimerUsed[i] = false;
            timer = &Timers[i];
            break;
        }
    }

    if (!found) Kernel::Assert();

    return timer;
}

void TimerProvider::Release(Timer timer) {
    timer.Stop();

    for (uint32 i = 0; i < NUM_TIMER; i++) {
        if (timer.BaseAddress == TIMER_ADDRESS[i]) {
            TimerUsed[i] = false;
            break;
        }
    }
}

void Timer::Initialize(uint32 baseAddress) {
    BaseAddress = baseAddress;

    TIM_CR1   = (TIM_CR1_reg   *)(baseAddress + TIM_CR1_OFFSET);
    TIM_DIER  = (TIM_DIER_reg  *)(baseAddress + TIM_DIER_OFFSET);
    TIM_SR    = (TIM_SR_reg    *)(baseAddress + TIM_SR_OFFSET);
    TIM_EGR   = (TIM_EGR_reg   *)(baseAddress + TIM_EGR_OFFSET);
    TIM_CCMR1 = (TIM_CCMR1_reg *)(baseAddress + TIM_CCMR1_OFFSET);
    TIM_CCER  = (TIM_CCER_reg  *)(baseAddress + TIM_CCER_OFFSET);
    TIM_CNT   = (TIM_CNT_reg   *)(baseAddress + TIM_CNT_OFFSET);
    TIM_PSC   = (TIM_PSC_reg   *)(baseAddress + TIM_PSC_OFFSET);
    TIM_ARR   = (TIM_ARR_reg   *)(baseAddress + TIM_ARR_OFFSET);
}

uint32 Timer::Setup(uint16 preScaler, uint16 autoReload) {
    // Timer expire in 0.004096 sec if preScaler = 0, autoReload = 0xffff
    PreScaler = preScaler;
    AutoReload = autoReload;

    // Stop counter
    TIM_CR1->CEN = false;

    // Load register
    TIM_PSC->PCS = preScaler;
    TIM_ARR->ARR = autoReload;

    // Apply change
    TIM_EGR->UG = true;

    // Return max countable milli sec
    uint32 preScaledClock = HSI_CLOCK / (PreScaler + 1);
    return AutoReload / preScaledClock * 1000;
}

void Timer::Start() {
    TIM_CR1->CEN = true;
}

void Timer::Stop() {
    TIM_CR1->CEN = false;
}

void Timer::Reset() {
    TIM_EGR->UG = true;
}

uint32 Timer::GetElapseMs() {
    uint32 currentCount = TIM_CNT->CNT;
    
    uint32 preScaledClock = HSI_CLOCK / (PreScaler + 1);

    return currentCount / preScaledClock * 1000;
}
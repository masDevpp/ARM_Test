#include "LEDHandler.h"
#include "Kernel.h"
#include "Trace.h"

Timer *LEDHandler::LEDTimer;

void LEDHandler::Setup() {
    LED::Setup();
    LED::Set(true);

    LEDTimer = TimerProvider::GetInstance();

    Trace::Add("LEDTimer", (uint32)LEDTimer);

    LEDTimer->Setup(0x0100);
    LEDTimer->Start();

    Loop();
}

void LEDHandler::Loop() {
    uint32 i = 0;
    while (true) {
        uint32 ledWait = (i < 50) ? BLINK_MS_FAST : BLINK_MS_SLOW;
        uint32 ledElapseMs = LEDTimer->GetElapseMs();

        if (ledElapseMs < ledWait) {
            Kernel::ThreadSleep();
            continue;
        } else {
            LED::Set(!LED::Get());
            LEDTimer->Reset();
            i++;
        }
    }
}
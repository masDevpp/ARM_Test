#pragma once
#include "DataType.h"
#include "LED.h"
#include "Timer.h"

class LEDHandler {
public:
    static void Setup();
    static void Loop();

private:
    static const uint32 BLINK_MS_FAST = 50;
    static const uint32 BLINK_MS_SLOW = 500;

    static Timer *LEDTimer;
};

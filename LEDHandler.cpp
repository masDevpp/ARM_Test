#include "LEDHandler.h"

void LEDHandler::Setup() {
    LED::Setup();
    LED::Set(true);
    Loop();
}

void LEDHandler::Loop() {
    for (uint32 i = 0; ; i++) {
        LED::Set(!LED::Get());

        int waitLoop = (i < 50) ? 50000 : 100000;
        for (int i = 0; i < waitLoop; i++);
    }
}
#include "LEDHandler.h"

void LEDHandler::Setup() {
    LEDManager::Setup();
    LEDManager::SetLED(true);
    Loop();
}

void LEDHandler::Loop() {
    for (uint32 i = 0; ; i++) {
        LEDManager::SetLED(!LEDManager::GetLED());

        int waitLoop = (i < 50) ? 50000 : 400000;
        for (int i = 0; i < waitLoop; i++);
    }
}
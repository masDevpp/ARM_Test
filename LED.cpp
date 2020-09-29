//#pragma G++ target ("thumb")
#include "LED.h"

LEDManager::LEDManager() {
    // LED (LD2) is connected to pin5 of GPIOA (PA5)
    GPIOA_MODER->MODER5 = GPIO_MODER_OUTPUT;
}

void LEDManager::SetLED(bool isOn) {
    if (isOn) {
        GPIOA_BSRR->BS5 = 1;
    } else {
        GPIOA_BSRR->BR5 = 1;
    }
}
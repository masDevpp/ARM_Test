//#pragma G++ target ("thumb")
#include "LED.h"

void LEDManager::SetupLED() {
    // LED (LD2) is connected to PA5 of GPIOA
    *((uint32 *)GPIOA_MODER) |= GPIOA_MODER_PA5_OUTPUT_MODE_MASK;
}

void LEDManager::SetLED(bool isOn) {
    if (isOn) {
        *((uint32 *)GPIOA_BSRR) |= GPIOA_BSRR_PA5_SET_MASK;
    } else {
        *((uint32 *)GPIOA_BSRR) |= GPIOA_BSRR_PA5_RESET_MASK;
    }
}
//#pragma G++ target ("thumb")
#include "LED.h"

void LEDManager::SetupLED() {
    // GPIOA clock enable by RCC_AHB1ENR
    *((uint32 *)RCC_AHB1ENR) |= RCC_AHB1ENR_GPIOAEN_MASK;

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
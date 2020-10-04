#include "LED.h"

volatile GPIO_MODER *LEDManager::GPIOA_MODER = (GPIO_MODER *)(GPIOA + 0x00);
volatile GPIO_ODR   *LEDManager::GPIOA_ODR   = (GPIO_ODR   *)(GPIOA + 0x14);
volatile GPIO_BSRR  *LEDManager::GPIOA_BSRR  = (GPIO_BSRR  *)(GPIOA + 0x18);

void LEDManager::Setup() {
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

bool LEDManager::GetLED() {
    return GPIOA_ODR->ODR5;
}
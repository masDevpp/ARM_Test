#include "LED.h"

volatile GPIO_MODER *LED::GPIOA_MODER = (GPIO_MODER *)(GPIOA + 0x00);
volatile GPIO_ODR   *LED::GPIOA_ODR   = (GPIO_ODR   *)(GPIOA + 0x14);
volatile GPIO_BSRR  *LED::GPIOA_BSRR  = (GPIO_BSRR  *)(GPIOA + 0x18);

void LED::Setup() {
    // LED (LD2) is connected to pin5 of GPIOA (PA5)
    GPIOA_MODER->MODER5 = GPIO_MODER_OUTPUT;
}

void LED::Set(bool isOn) {
    if (isOn) {
        GPIOA_BSRR->BS5 = 1;
    } else {
        GPIOA_BSRR->BR5 = 1;
    }
}

bool LED::Get() {
    return GPIOA_ODR->ODR5;
}
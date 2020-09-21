#pragma GCC target ("thumb")
#include "main.h"

int GlobalInt = 3;
int GlobalInt2 = 3;
int GlobalIntUninit;

extern char _data_load_source[];
extern char _data_load_size[];
extern char _data_load_destinatin[];
extern char _bss_address[];
extern char _bss_size[];

int main() {
    loadMemory();

    int a = 0;
    int b = 2;
    GlobalIntUninit = a + b + GlobalInt;
    GlobalInt2 = GlobalIntUninit * 2;
    
    setupLED();
    
    uint32 ledOn = 1;
    while (1) {
        if (ledOn == 1) {
            setLEDOn();
            ledOn = 0;
        } else {
            setLEDOff();
            ledOn = 1;
        }

        for (int i = 0; i < 1000000; i++);
    }

    return 0;
}

void loadMemory() {
    // Load data section from ROM to RAM
    for (int i = 0; i < (unsigned int)_data_load_size; i++) {
        _data_load_destinatin[i] = _data_load_source[i];
    }

    // Zero clear bss section
    for (int i = 0; i < (unsigned int)_bss_size; i++) {
        _bss_address[i] = 0;
    }
}
void setupLED() {
    // GPIOA clock enable by RCC_AHB1ENR
    *((uint32 *)RCC_AHB1ENR) |= RCC_AHB1ENR_GPIOAEN_MASK;

    // LED (LD2) is connected to PA5 of GPIOA
    *((uint32 *)GPIOA_MODER) |= GPIOA_MODER_PA5_OUTPUT_MODE_MASK;
}

void setLEDOn() {
    *((uint32 *)GPIOA_BSRR) |= GPIOA_BSRR_PA5_SET_MASK;
}

void setLEDOff() {
    *((uint32 *)GPIOA_BSRR) |= GPIOA_BSRR_PA5_RESET_MASK;
}
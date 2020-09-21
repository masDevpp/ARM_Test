typedef signed char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;

// GPIOA
const uint32 GPIOA        = 0x40020000;
const uint32 GPIOA_MODER  = GPIOA + 0x00;
const uint32 GPIOA_OTYPER = GPIOA + 0x04;
const uint32 GPIOA_ODR    = GPIOA + 0x14;
const uint32 GPIOA_BSRR   = GPIOA + 0x18;

const uint32 GPIOA_MODER_PA5_OUTPUT_MODE_MASK = 0x00000400;
const uint32 GPIOA_ODR_PA5_MASK = 0x00000020;
const uint32 GPIOA_BSRR_PA5_SET_MASK = 0x00000020;
const uint32 GPIOA_BSRR_PA5_RESET_MASK = 0x00200000;

// RCC
const uint32 RCC          = 0x40023800;
const uint32 RCC_AHB1ENR  = RCC + 0x30;

const uint32 RCC_AHB1ENR_GPIOAEN_MASK = 0x00000001;

int main();

void loadMemory();
void systemSetup();

void setupLED();
void setLEDOn();
void setLEDOff();
#pragma once
#include "DataType.h"

// GPIO port mode register
// Offset 0x00
typedef struct GPIO_MODER_struct {
    uint32 MODER0  : 2;
    uint32 MODER1  : 2;
    uint32 MODER2  : 2;
    uint32 MODER3  : 2;
    uint32 MODER4  : 2;
    uint32 MODER5  : 2;
    uint32 MODER6  : 2;
    uint32 MODER7  : 2;
    uint32 MODER8  : 2;
    uint32 MODER9  : 2;
    uint32 MODER10 : 2;
    uint32 MODER11 : 2;
    uint32 MODER12 : 2;
    uint32 MODER13 : 2;
    uint32 MODER14 : 2;
    uint32 MODER15 : 2;
} GPIO_MODER;

const uint32 GPIO_MODER_INPUT = 0;
const uint32 GPIO_MODER_OUTPUT = 1;
const uint32 GPIO_MODER_ALTERNATE_FUNCTION = 2;
const uint32 GPIO_MODER_ANALOG = 3;

// GPIO port output type register
// Offset 0x04
typedef struct GPIO_OTYPER_struct {
    uint32 OT0  : 1;
    uint32 OT1  : 1;
    uint32 OT2  : 1;
    uint32 OT3  : 1;
    uint32 OT4  : 1;
    uint32 OT5  : 1;
    uint32 OT6  : 1;
    uint32 OT7  : 1;
    uint32 OT8  : 1;
    uint32 OT9  : 1;
    uint32 OT10 : 1;
    uint32 OT11 : 1;
    uint32 OT12 : 1;
    uint32 OT13 : 1;
    uint32 OT14 : 1;
    uint32 OT15 : 1;
    uint32      : 16;
} GPIO_OTYPER;

// GPIO port output data register
// Offset 0x14
typedef struct GPIO_ODR_struct {
    uint32 ODR0  : 1;
    uint32 ODR1  : 1;
    uint32 ODR2  : 1;
    uint32 ODR3  : 1;
    uint32 ODR4  : 1;
    uint32 ODR5  : 1;
    uint32 ODR6  : 1;
    uint32 ODR7  : 1;
    uint32 ODR8  : 1;
    uint32 ODR9  : 1;
    uint32 ODR10 : 1;
    uint32 ODR11 : 1;
    uint32 ODR12 : 1;
    uint32 ODR13 : 1;
    uint32 ODR14 : 1;
    uint32 ODR15 : 1;
    uint32       : 16;
} GPIO_ODR;

// GPIO port bit set/reset register
// Offset 0x18
typedef struct GPIO_BSRR_struct {
    uint32 BS0  : 1;
    uint32 BS1  : 1;
    uint32 BS2  : 1;
    uint32 BS3  : 1;
    uint32 BS4  : 1;
    uint32 BS5  : 1;
    uint32 BS6  : 1;
    uint32 BS7  : 1;
    uint32 BS8  : 1;
    uint32 BS9  : 1;
    uint32 BS10 : 1;
    uint32 BS11 : 1;
    uint32 BS12 : 1;
    uint32 BS13 : 1;
    uint32 BS14 : 1;
    uint32 BS15 : 1;
    uint32 BR0  : 1;
    uint32 BR1  : 1;
    uint32 BR2  : 1;
    uint32 BR3  : 1;
    uint32 BR4  : 1;
    uint32 BR5  : 1;
    uint32 BR6  : 1;
    uint32 BR7  : 1;
    uint32 BR8  : 1;
    uint32 BR9  : 1;
    uint32 BR10 : 1;
    uint32 BR11 : 1;
    uint32 BR12 : 1;
    uint32 BR13 : 1;
    uint32 BR14 : 1;
    uint32 BR15 : 1;
} GPIO_BSRR;

// GPIO alternate function low register
// Offset 0x20
typedef struct GPIO_AFRL_struct {
    uint32 AFRL0 : 4;
    uint32 AFRL1 : 4;
    uint32 AFRL2 : 4;
    uint32 AFRL3 : 4;
    uint32 AFRL4 : 4;
    uint32 AFRL5 : 4;
    uint32 AFRL6 : 4;
    uint32 AFRL7 : 4;
} GPIO_AFRL;

// GPIO alternate function high register
// Offset 0x24
typedef struct GPIO_AFRH_struct {
    uint32 AFRH0 : 4;
    uint32 AFRH1 : 4;
    uint32 AFRH2 : 4;
    uint32 AFRH3 : 4;
    uint32 AFRH4 : 4;
    uint32 AFRH5 : 4;
    uint32 AFRH6 : 4;
    uint32 AFRH7 : 4;
} GPIO_AFRH;

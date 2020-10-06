#pragma once
#include "DataType.h"

// RCC clock control register
// Offset 0x00
typedef struct RCC_CR_struct {
    uint32 HSION      : 1;
    uint32 HSIRDY     : 1;
    uint32            : 1;
    uint32 HSITRIM    : 5;
    uint32 HSICAL     : 8;
    uint32 HSEON      : 1;
    uint32 HSERDY     : 1;
    uint32 HSEBYP     : 1;
    uint32 CSSON      : 1;
    uint32            : 4;
    uint32 PLL_ON     : 1;
    uint32 PLL_RDY    : 1;
    uint32 PLL_I2SON  : 1;
    uint32 PLL_I2SRDY : 1;
    uint32 PLL_SAION  : 1;
    uint32 PLL_SAIRDY : 1;
    uint32            : 2;
} RCC_CR_reg;

// RCC AHB1 peripheral clock enable register
// Offset 0x30
typedef struct RCC_AHB1ENR_struct {
    uint32 GPIOAEN     : 1;
    uint32 GPIOBEN     : 1;
    uint32 GPIOCEN     : 1;
    uint32 GPIODEN     : 1;
    uint32 GPIOEEN     : 1;
    uint32 GPIOFEN     : 1;
    uint32 GPIOGEN     : 1;
    uint32 GPIOHEN     : 1;
    uint32             : 4;
    uint32 CRCEN       : 1;
    uint32             : 5;
    uint32 BKPSRAMEN   : 1;
    uint32             : 2;
    uint32 DMA1EN      : 1;
    uint32 DMA2EN      : 1;
    uint32             : 6;
    uint32 OTGHSEN     : 1;
    uint32 OTGHSULPIEN : 1;
    uint32             : 1;
} RCC_AHB1ENR_reg;

// RCC AHB2 peripheral clock enable register
// Offset 0x34
typedef struct RCC_AHB2ENR_struct {
    uint32 DCMIEN  : 1;
    uint32         : 6;
    uint32 OTGFSEN : 1;
    uint32         : 24;
} RCC_AHB2ENR_reg;

// RCC AHB3 peripheral clock enable register
// Offset 0x38
typedef struct RCC_AHB3ENR_struct {
    uint32 FMCEN  : 1;
    uint32 QSPIEN : 1;
    uint32        : 30;
} RCC_AHB3ENR_reg;

// RCC APB1 peripheral clock enable register
// Offset 0x40
typedef struct RCC_APB1ENR_struct {
    uint32 TIM2EN    : 1;
    uint32 TIM3EN    : 1;
    uint32 TIM4EN    : 1;
    uint32 TIM5EN    : 1;
    uint32 TIM6EN    : 1;
    uint32 TIM7EN    : 1;
    uint32 TIM12EN   : 1;
    uint32 TIM13EN   : 1;
    uint32 TIM14EN   : 1;
    uint32           : 2;
    uint32 WWDGEN    : 1;
    uint32           : 2;
    uint32 SPI2EN    : 1;
    uint32 SPI3EN    : 1;
    uint32 SPDIFRXEN : 1;
    uint32 USART2EN  : 1;
    uint32 USART3EN  : 1;
    uint32 UART4EN   : 1;
    uint32 UART5EN   : 1;
    uint32 I2C1EN    : 1;
    uint32 I2C2EN    : 1;
    uint32 I2C3EN    : 1;
    uint32 FMPI2C1EN : 1;
    uint32 CAN1EN    : 1;
    uint32 CAN2EN    : 1;
    uint32 CECEN     : 1;
    uint32 PWREN     : 1;
    uint32 DACEN     : 1;
    uint32           : 2;
} RCC_APB1ENR_reg;

// RCC APB2 peripheral clock enable register
// Offset 0x44
typedef struct RCC_APB2ENR_struct {
    uint32 TIM1EN   : 1;
    uint32 TIM8EN   : 1;
    uint32          : 2;
    uint32 USART1EN : 1;
    uint32 USART6EN : 1;
    uint32          : 2;
    uint32 ADC1EN   : 1;
    uint32 ADC2EN   : 1;
    uint32 ADC3EN   : 1;
    uint32 SDIOEN   : 1;
    uint32 SPI1EN   : 1;
    uint32 SPI4EN   : 1;
    uint32 SYSCFGEN : 1;
    uint32          : 1;
    uint32 TIM9EN   : 1;
    uint32 TIM10EN  : 1;
    uint32 TIM11EN  : 1;
    uint32          : 3;
    uint32 SAI1EN   : 1;
    uint32 SAI2EN   : 1;
    uint32          : 8;
} RCC_APB2ENR_reg;

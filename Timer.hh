#pragma once
#include "DataType.h"
//
// TIM10/11/13/14 register
//

// TIM10/11/13/14 control register 1
// Offset 0x00
typedef struct TIM_CR1_reg_struct {
    uint32 CEN  : 1;
    uint32 UDIS : 1;
    uint32 URS  : 1;
    uint32      : 4;
    uint32 ARPE : 1;
    uint32 CKD  : 2;
} TIM_CR1_reg;

// TIM10/11/13/14 Interrupt enable register
// Offset 0x0c
typedef struct TIM_DIER_reg_struct {
    uint32 UIE   : 1;
    uint32 CC1IE : 1;
} TIM_DIER_reg;

// TIM10/11/13/14 status register
// Offset 0x10
typedef struct TIM_SR_reg_struct {
    uint32 UIF   : 1;
    uint32 CC1IF : 1;
    uint32       : 7;
    uint32 CC1OF : 1;
} TIM_SR_reg;

// TIM10/11/13/14 event generation register
// Offset 0x14
typedef struct TIM_EGR_reg_struct {
    uint32 UG   : 1;
    uint32 CC1G : 1;
} TIM_EGR_reg;

// TIM10/11/13/14 capture/compare mode register 1
// Offset 0x18
typedef struct TIM_CCMR1_reg_struct {
    uint32 CC1S  : 2;
    uint32 OC1FE : 1;
    uint32 OC1PE : 1;
    uint32 OC1M  : 2;
} TIM_CCMR1_reg;

// TIM10/11/13/14 capture/compare enable register
// Offset 0x20
typedef struct TIM_CCER_reg_struct {
    uint32 CC1E : 1;
    uint32 CC1P : 1;
    uint32      : 1;
    uint32 CC1NP : 1;
} TIM_CCER_reg;

// TIM10/11/13/14 counter
// Offset 0x24
typedef struct TIM_CNT_reg_struct {
    uint32 CNT : 16;
} TIM_CNT_reg;

// TIM10/11/13/14 prescaler
// Offset 0x28
typedef struct TIM_PSC_reg_struct {
    uint32 PCS : 16;
} TIM_PSC_reg;

// TIM10/11/13/14 auto-reload register
// Offset 0x2c
typedef struct TIM_ARR_reg_struct {
    uint32 ARR : 16;
} TIM_ARR_reg;
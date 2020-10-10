#pragma once
#include "DataType.h"

// SysTick Control and Status Register, SYST_CSR
// 0xE000E010
typedef struct SYST_CSR_reg_struct {
    uint32 ENABLE    : 1;
    uint32 TICKINT   : 1;
    uint32 CLKSOURCE : 1;
    uint32           : 13;
    uint32 COUNTFLAG : 1;
} SYST_CSR_reg;

// SysTick Reload Value Register, SYST_RVR
// 0xE000E014
typedef struct SYST_RVR_reg_struct {
    uint32 RELOAD : 24;    
} SYST_RVR_reg;

//SysTick Current Value Register, SYST_CVR
// 0xE000E018
typedef struct SYST_CVR_reg_struct {
    uint32 CURRENT;
} SYST_CVR_reg;

// SysTick Calibration value Register, SYST_CALIB
// 0xE000E01C
typedef struct SYST_CALIB_reg_struct {
    uint32 TENMS : 24;
    uint32       : 6;
    uint32 SKEW  : 1;
    uint32 NOREF : 1;
} SYST_CALIB;

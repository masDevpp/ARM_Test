#pragma once
#include "DataType.h"

typedef struct USART_SR_struct {
    uint32 PE   : 1;
    uint32 FE   : 1;
    uint32 NF   : 1;
    uint32 ORE  : 1;
    uint32 IDLE : 1;
    uint32 RXNE : 1;
    uint32 TC   : 1;
    uint32 TXE  : 1;
    uint32 LBD  : 1;
    uint32 CTS  : 1;
    uint32      : 22;
} USART_SR;

typedef struct USART_DR_struct {
    uint32 DR : 8;
    uint32    : 24;
} USART_DR;

typedef struct USART_BRR_struct {
    uint32 DIV_Fraction : 4;
    uint32 DIV_Mantissa : 12;
    uint32              : 16;
} USART_BRR;

const uint32 USART_BRR_9800_FRACTION = 0x3;
const uint32 USART_BRR_9800_MANTISSA = 0x68;
const uint32 USART_BRR_115200_FRACTION = 0xb;
const uint32 USART_BRR_115200_MANTISSA = 0x8;
const uint32 USART_BRR_230400_FRACTION = 0x5;
const uint32 USART_BRR_230400_MANTISSA = 0x4;

typedef struct USART_CR1_struct {
    uint32 SBK    : 1;
    uint32 PWU    : 1;
    uint32 RE     : 1;
    uint32 TE     : 1;
    uint32 IDLEIE : 1; // bit4
    uint32 RXNEIE : 1;
    uint32 TCIE   : 1;
    uint32 TXEIE  : 1;
    uint32 PEIE   : 1; // bit8
    uint32 PS     : 1;
    uint32 PCE    : 1;
    uint32 WAKE   : 1;
    uint32 M      : 1; // bit12
    uint32 UE     : 1;
    uint32        : 1;
    uint32 OVER8  : 1;
    uint32        : 16;
} USART_CR1;

typedef struct USART_CR2_struct {
    uint32 ADD   : 4;
    uint32       : 1;
    uint32 LBDL  : 1;
    uint32 LBDIE : 1;
    uint32       : 1;
    uint32 LBCL  : 1;
    uint32 CPHA  : 1;
    uint32 CPOL  : 1;
    uint32 CLKEN : 1;
    uint32 STOP  : 2;
    uint32 LINEN : 1;
    uint32       : 17;
} USART_CR2;

typedef struct USART_CR3_struct {
    uint32 EIE    : 1;
    uint32 IREN   : 1;
    uint32 IRLP   : 1;
    uint32 HDSEL  : 1;
    uint32 NACK   : 1;
    uint32 SCEN   : 1;
    uint32 DMAR   : 1;
    uint32 DMAT   : 1;
    uint32 RTSE   : 1;
    uint32 CTSE   : 1;
    uint32 CTSIE  : 1;
    uint32 ONEBIT : 1;
    uint32        : 20;
} USART_CR3;

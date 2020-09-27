#include "SerialHandler.h"

bool SerialInterrupted = false;
uint32 StatusRegisterDump ;
uint32 DataDump;
uint32 DataDump2;

void SerialInt() {
    SerialInterrupted = true;
    StatusRegisterDump = *((uint32 *)0x40004400);
    DataDump = *((uint32 *)0x40004404);
    DataDump2 = *((uint32 *)0x40004404);
}

void SerialHandler::Setup() {
    // Setup GPIO mode
    *GPIOA_MODER &= ~(GPIOA_MODR_MODER2_MASK | GPIOA_MODR_MODER3_MASK);
    *GPIOA_MODER |= GIPOA_MODR_AF << GPIOA_MODR_MODER2_SHIFT;
    *GPIOA_MODER |= GIPOA_MODR_AF << GPIOA_MODR_MODER3_SHIFT;

    // Set GPIO alternate function as USART
    *GPIOA_AFRL &= ~(GPIOA_AFRL_AFRL2_MASK | GPIOA_AFRL_AFRL3_MASK);
    *GPIOA_AFRL |= GPIOA_AFRL_AF7 << GPIOA_AFRL_AFRL2_SHIFT;
    *GPIOA_AFRL |= GPIOA_AFRL_AF7 << GPIOA_AFRL_AFRL3_SHIFT;

    // Set UART enable
    *USART2_CR1 |= USART2_CR1_UE_MASK;

    // Parity disable
    *USART2_CR1 &= ~USART2_CR1_PCE_MASK;

    // Set word length as 1 Start bit, 8 Data bits, n Stop bit by negate M bit
    *USART2_CR1 &= ~USART2_CR1_M_MASK;

    // Set 1 stop bit by set 0 to STOP
    *USART2_CR2 &= ~USART2_CR2_STOP_MASK;

    // Set DMA disable
    *USART2_CR3 &= ~(USART2_CR3_DMAR_MASK | USART2_CR3_DMAT_MASK);

    uint32 oversample = ((*USART2_CR1 & USART2_CR1_OVER8_MASK) == 0) ? 16 : 8;
    // Baud rate 9800
    // Set 104.1875(0x683) for oversample 16 or 208.375(0xD03) for oversample 8
    *USART2_BRR = oversample == 16 ? 0x683 : 0xd03;

    // Serial receive and interrupt enable
    *USART2_CR1 |= (USART2_CR1_RXNEIE_MASK | USART2_CR1_RE_MASK);
    
    // Set NVIC USART2 global interrupt enable
    *NVIC_ISER1 |= NVIC_ISER1_USART2_GLOBAL_INT_MASK;
}

void SerialHandler::SendByte(uint8 data) {

    if (((*USART2_SR & USART2_SR_TXE_MASK) != 0) &&
        ((*USART2_SR & USART2_SR_TC_MASK) != 0) &&
        ((*USART2_SR & USART2_SR_RXNE_MASK) == 0) &&
        ((*USART2_CR1 & USART2_CR1_TE_MASK) == 0)) {
        // Set transmit enable
        *USART2_CR1 |= USART2_CR1_TE_MASK;

        // Write data
        *USART2_DR = data;

        // Wait transmit complete
        while ((*USART2_SR & USART2_SR_TC_MASK) == 0);
        *USART2_CR1 &= ~USART2_CR1_TE_MASK;
    }
}

void SerialHandler::SendString(char *chars) {
    char data = *chars++;

    while (data != '\0') {
        SendByte(data);
        data = *chars++;
    }
}
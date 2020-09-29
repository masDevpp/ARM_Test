#include "SerialHandler.h"

const uint32 SerialBufferLength = 0x80;
uint8 SerialBuffer[SerialBufferLength];
uint32 SerialBufferIndex = 0;

void SerialHandler::SerialInt() {
    
    if (USART2_SR->RXNE) {
        uint8 data = ReceiveByte();
        LFReceived = data == '\n';
        CRReceived = data == '\r';

        SerialBuffer[SerialBufferIndex++] = data;

        if (LFReceived && CRReceived) {
            SerialBuffer[SerialBufferIndex] = '\0';
            SerialBufferIndex = 0;
            LFReceived = false;
            CRReceived = false;
        }
    }
}

void SerialHandler::Setup() {
    // Setup GPIO mode
    GPIOA_MODER->MODER2 = GPIO_MODER_ALTERNATE_FUNCTION;
    GPIOA_MODER->MODER3 = GPIO_MODER_ALTERNATE_FUNCTION;

    // Set GPIO alternate function as USART by set AF7
    GPIOA_AFRL->AFRL2 = 7;
    GPIOA_AFRL->AFRL3 = 7;
    
    // Set UART enable
    USART2_CR1->UE = true;

    // Parity disable
    USART2_CR1->PCE = 0;

    // Set word length as 1 Start bit, 8 Data bits, n Stop bit by negate M bit
    USART2_CR1->M = 0;

    // Set 1 stop bit by set 0 to STOP
    USART2_CR2->STOP = 0;

    // Set DMA disable
    USART2_CR3->DMAR = 0;
    USART2_CR3->DMAT = 0;

    // Set oversample by 16
    USART2_CR1->OVER8 = 0;

    // Set 104.1875(0x683) for baud rate 9800
    USART2_BRR->DIV_Fraction = USART_BRR_9800_FRACTION;
    USART2_BRR->DIV_Mantissa = USART_BRR_9800_MANTISSA;

    // Serial receive and interrupt enable
    USART2_CR1->TE = 1;
    USART2_CR1->RE = 1;
    USART2_CR1->RXNEIE = 1;

    // Set NVIC USART2 global interrupt enable
    *NVIC_ISER1 |= NVIC_ISER1_USART2_GLOBAL_INT_MASK;
}

void SerialHandler::SendByte(uint8 data) {
    if (USART2_SR->TXE == 1 && USART2_SR->TC == 1) {
        
        USART2_DR->DR = data;

        while (USART2_SR->TC == 0);
    }
}

void SerialHandler::SendString(char *chars) {
    char data = *chars++;

    while (data != '\0') {
        SendByte(data);
        data = *chars++;
    }
}

uint8 SerialHandler::ReceiveByte() {
    uint8 data = USART2_DR->DR;
    return data;
}
#include "SerialHandler.h"

volatile GPIO_MODER *SerialHandler::GPIOA_MODER = (GPIO_MODER *)(GPIOA + 0x00);
volatile GPIO_AFRL  *SerialHandler::GPIOA_AFRL  = (GPIO_AFRL  *)(GPIOA + 0x20);

volatile USART_SR  *SerialHandler::USART2_SR  = (USART_SR  *)(USART2 + 0x00);
volatile USART_DR  *SerialHandler::USART2_DR  = (USART_DR  *)(USART2 + 0x04);
volatile USART_BRR *SerialHandler::USART2_BRR = (USART_BRR *)(USART2 + 0x08);
volatile USART_CR1 *SerialHandler::USART2_CR1 = (USART_CR1 *)(USART2 + 0x0c);
volatile USART_CR2 *SerialHandler::USART2_CR2 = (USART_CR2 *)(USART2 + 0x10);
volatile USART_CR3 *SerialHandler::USART2_CR3 = (USART_CR3 *)(USART2 + 0x14);

bool SerialHandler::IsReceiveComplete = false;
bool SerialHandler::CRReceived = false;
bool SerialHandler::LFReceived = false;

uint8 *SerialHandler::SerialBuffer;
uint32 SerialHandler::SerialBufferIndex = 0;
uint8 SerialHandler::LastReceiveByte;

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
    USART2_CR1->PCE = false;

    // Set word length as 1 Start bit, 8 Data bits, n Stop bit by negate M bit
    USART2_CR1->M = false;

    // Set 1 stop bit by set 0 to STOP
    USART2_CR2->STOP = false;

    // Set DMA disable
    USART2_CR3->DMAR = false;
    USART2_CR3->DMAT = false;

    // Set oversample by 16
    USART2_CR1->OVER8 = false;

    // Set 104.1875(0x683) for baud rate 9800
    USART2_BRR->DIV_Fraction = USART_BRR_9800_FRACTION;
    USART2_BRR->DIV_Mantissa = USART_BRR_9800_MANTISSA;

    // Serial receive and interrupt enable
    USART2_CR1->TE = true;
    USART2_CR1->RE = true;
    USART2_CR1->RXNEIE = true;

    // Set NVIC USART2 global interrupt enable
    *(uint32 *)NVIC_ISER1 |= NVIC_ISER1_USART2_GLOBAL_INT_MASK;

    // Serial receive buffer
    SerialBuffer = (uint8 *)Memory::Allocate(SERIAL_BUFFER_LENGTH);
}

void SerialHandler::SendByte(uint8 data) {
    if (USART2_SR->TXE && USART2_SR->TC) {
        
        USART2_DR->DR = data;

        while (USART2_SR->TC == false);
    }
}

void SerialHandler::SendString(const void *str) {
    char *chars = (char *)str;
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

void SerialHandler::SerialInterrupt() {
    LastReceiveByte = 0;

    if (USART2_SR->RXNE) {
        uint8 data = ReceiveByte();
        LFReceived = data == '\n';
        CRReceived = data == '\r';

        SerialBuffer[SerialBufferIndex++] = data;
        LastReceiveByte = data;

        if (CRReceived || (SerialBufferIndex == SERIAL_BUFFER_LENGTH - 1)) {
            SerialBuffer[SerialBufferIndex] = '\0';
            SerialBufferIndex = 0;
            LFReceived = false;
            CRReceived = false;
            IsReceiveComplete = true;
        } else {
            IsReceiveComplete = false;
        }
    }
}
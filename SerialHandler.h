#include "DataType.h"
#include "SerialHandler.hh"
#include "GPIO.hh"

class SerialHandler {
public:
    void Setup();
    void SendByte(uint8 data);
    void SendString(char *chars);
    uint8 ReceiveByte();
    void SerialInt();

private:
    bool CRReceived = false;
    bool LFReceived = false;

    // GPIOA
    uint32 GPIOA = 0x40020000;
    volatile GPIO_MODER *GPIOA_MODER = (GPIO_MODER *)(GPIOA + 0x00);
    volatile GPIO_AFRL  *GPIOA_AFRL  = (GPIO_AFRL  *)(GPIOA + 0x20);

    // USART2
    uint32 USART2 = 0x40004400;
    volatile USART_SR  *USART2_SR  = (USART_SR  *)(USART2 + 0x00);
    volatile USART_DR  *USART2_DR  = (USART_DR  *)(USART2 + 0x04);
    volatile USART_BRR *USART2_BRR = (USART_BRR *)(USART2 + 0x08);
    volatile USART_CR1 *USART2_CR1 = (USART_CR1 *)(USART2 + 0x0c);
    volatile USART_CR2 *USART2_CR2 = (USART_CR2 *)(USART2 + 0x10);
    volatile USART_CR3 *USART2_CR3 = (USART_CR3 *)(USART2 + 0x14);
    
    // NVIC
    uint32 *NVIC_ISER1 = (uint32 *)0xE000E104;
    uint32 NVIC_ISER1_USART2_GLOBAL_INT_MASK = 0x00000040;
};


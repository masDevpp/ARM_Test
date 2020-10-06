#include "DataType.h"
#include "USART.hh"
#include "GPIO.hh"
#include "Memory.h"

class SerialHandler {
public:
    static void Setup();
    static void SendByte(uint8 data);
    static void SendString(char *chars);
    static uint8 ReceiveByte();
    static void SerialInterrupt();

    static bool IsReceiveComplete;// = false;
    static const uint32 SERIAL_BUFFER_LENGTH = Memory::SEGMENT_SIZE;
    static uint8 *SerialBuffer;

private:
    static uint32 SerialBufferIndex;

    static bool CRReceived; // Carriadge return (\r) (0x0d)
    static bool LFReceived; // Line feed (\n) (0x0a)

    // GPIOA
    static const uint32 GPIOA = 0x40020000;
    static volatile GPIO_MODER *GPIOA_MODER;// = (GPIO_MODER *)(0x40020000 + 0x00);
    static volatile GPIO_AFRL  *GPIOA_AFRL;//  = (GPIO_AFRL  *)(GPIOA + 0x20);

    // USART2
    static const uint32 USART2 = 0x40004400;
    static volatile USART_SR  *USART2_SR;//  = (USART_SR  *)(USART2 + 0x00);
    static volatile USART_DR  *USART2_DR;//  = (USART_DR  *)(USART2 + 0x04);
    static volatile USART_BRR *USART2_BRR;// = (USART_BRR *)(USART2 + 0x08);
    static volatile USART_CR1 *USART2_CR1;// = (USART_CR1 *)(USART2 + 0x0c);
    static volatile USART_CR2 *USART2_CR2;// = (USART_CR2 *)(USART2 + 0x10);
    static volatile USART_CR3 *USART2_CR3;// = (USART_CR3 *)(USART2 + 0x14);
    
    // NVIC
    static const uint32 NVIC_ISER1 = 0xE000E104;
    static const uint32 NVIC_ISER1_USART2_GLOBAL_INT_MASK = 0x00000040;
};

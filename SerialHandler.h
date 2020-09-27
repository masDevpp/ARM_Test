#include "DataType.h"

class SerialHandler {
public:
    void Setup();
    void SendByte(uint8 data);
    void SendString(char *chars);

private:
    // GPIOA
    uint32 *GPIOA        = (uint32 *)0x40020000;
    uint32 *GPIOA_MODER  = GPIOA + 0;
    uint32 *GPIOA_AFRL   = GPIOA + 8;

    uint32 GPIOA_MODR_MODER2_MASK  = 0x00000030; // GPIO mode for pin 2
    uint32 GPIOA_MODR_MODER2_SHIFT = 4;
    uint32 GPIOA_MODR_MODER3_MASK  = 0x000000C0; // GPIO mode for pin 3
    uint32 GPIOA_MODR_MODER3_SHIFT = 6;
    uint32 GIPOA_MODR_AF           = 2;          // Alternate function mode

    uint32 GPIOA_AFRL_AFRL2_MASK   = 0x00000F00; // Alternate function for pin2
    uint32 GPIOA_AFRL_AFRL2_SHIFT  = 8;
    uint32 GPIOA_AFRL_AFRL3_MASK   = 0x0000F000; // Alternate function for pin2
    uint32 GPIOA_AFRL_AFRL3_SHIFT  = 12;
    uint32 GPIOA_AFRL_AF7          = 7;          // AF7 for USART2

    // USART2
    uint32 *USART2      = (uint32 *)0x40004400;
    uint32 *USART2_SR   = USART2 + 0;
    uint32 *USART2_DR   = USART2 + 1;
    uint32 *USART2_BRR  = USART2 + 2;
    uint32 *USART2_CR1  = USART2 + 3;
    uint32 *USART2_CR2  = USART2 + 4;
    uint32 *USART2_CR3  = USART2 + 5;
    uint32 *USART2_GTPR = USART2 + 6;

    uint32 USART2_SR_RXNE_MASK    = 0x00000020; // Read data register not empty
    uint32 USART2_SR_TC_MASK      = 0x00000040; // Transmission complete
    uint32 USART2_SR_TXE_MASK     = 0x00000080; // Transmit data register empty

    uint32 USART2_CR1_RE_MASK     = 0x00000004; // Receiver enable
    uint32 USART2_CR1_TE_MASK     = 0x00000008; // Transmitter enable
    uint32 USART2_CR1_RXNEIE_MASK = 0x00000020; // RXNE interrupt enable
    uint32 USART2_CR1_PCE_MASK    = 0x00000400; // Parity control enable
    uint32 USART2_CR1_M_MASK      = 0x00001000; // Word length
    uint32 USART2_CR1_UE_MASK     = 0x00002000; // UART enable
    uint32 USART2_CR1_OVER8_MASK  = 0x00010000; // Oversampling

    uint32 USART2_CR2_STOP_MASK   = 0x00003000;

    uint32 USART2_CR3_DMAR_MASK   = 0x00000040;
    uint32 USART2_CR3_DMAT_MASK   = 0x00000080;

    // NVIC
    uint32 *NVIC_ISER1 = (uint32 *)0xE000E104;
    uint32 NVIC_ISER1_USART2_GLOBAL_INT_MASK = 0x00000040;
};
// Set instruction as thumb
.code 16

// Interrupt vector table
// Refer Cortex-M4 Devices Generic User Guide 2.3.2 Exception types
// OR STM32F446xx Reference manual (RM0390) 10.1.3 Interrupt and exception vectors
.word   0 // 0x00
.word   _reset_handler + 1
.word   _nmi_handler + 1
.word   _hard_fault_handler + 1
.word   _mem_manage_handler + 1
.word   _bus_fault_handler + 1
.word   _usage_fault_handler + 1
.word   0
.word   0 // 0x20
.word   0
.word   0
.word   _sv_call_handler + 1
.word   0
.word   0
.word   _pend_sv_handler + 1
.word   _sys_tick_handler + 1

// Vector for STM32 96 interrupts
// Refer STM32F446 manual 10 Interrupts and events
.word   _irq_handler + 1 // 0x40
.word   0
.word   0
.word   0
.word   0 // 0x50
.word   0
.word   0
.word   0
.word   0 // 0x60
.word   0
.word   0
.word   0
.word   0 // 0x70
.word   0
.word   0
.word   0
.word   0 // 0x80
.word   0
.word   0
.word   0
.word   0 // 0x90
.word   0
.word   0
.word   0
.word   0 // 0xa0
.word   0
.word   0
.word   0
.word   0 // 0xb0
.word   0
.word   0
.word   0
.word   0 // 0xc0
.word   0
.word   0
.word   0
.word   0 // 0xd0
.word   0
.word   _usart2_handler + 1
.word   0
.word   0 // 0xe0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0
.word   0

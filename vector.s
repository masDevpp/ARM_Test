// Set instruction as thumb
.code 16

// Interrupt vector table
// Refer Cortex-M4 Devices Generic User Guide 2.3.2 Exception types
// OR STM32F446xx Reference manual (RM0390) 10.1.3 Interrupt and exception vectors
.word   0
.word   _reset_handler + 1
.word   _nmi_handler + 1
.word   _hard_fault_handler + 1
.word   _mem_manage_handler + 1
.word   _bus_fault_handler + 1
.word   _usage_fault_handler + 1
.word   0
.word   0
.word   0
.word   0
.word   _svc_call_handler + 1
.word   0
.word   0
.word   _pend_sv_handler + 1
.word   _sys_tick_handler + 1

// Vector for STM32 96 interrupts
// Refer STM32F446 manual 10 Interrupts and events
.word   _irq_handler + 1
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

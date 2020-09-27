// Set instruction as thumb
.code 16

.global _reset_handler
.global _nmi_handler
.global _hard_fault_handler
.global _mem_manage_handler
.global _bus_fault_handler
.global _usage_fault_handler
.global _svc_call_handler
.global _pend_sv_handler
.global _sys_tick_handler
.global _irq_handler
.global _usart2_handler

_reset_handler:
movw    fp, #0
ldr     r1, =_stack_bottom
mov     sp, r1
bl  main
b   _inf_loop

_nmi_handler:
mov r0, #1
b   _inf_loop

_hard_fault_handler:
push    {lr}
mov r0, #2
ldr r1, =0xE000ED2C // HFSR (Hard fault status register)
ldr r1, [r1]
ldr r2, =0xE000ED30 // DFSR (Degug fault status register)
ldr r2, [r2]
MRS r3, CONTROL
b   _inf_loop

_mem_manage_handler:
mov r0, #3
ldr r1, =0xE000ED34 // MMFAR (Mem manage fault address register)
ldr r1, [r1]
b   _inf_loop

_bus_fault_handler:
mov r0, #4
ldr r1, =0xE000ED38 // BFAR (Bus fault address register)
ldr r1, [r1]
b   _inf_loop

_usage_fault_handler:
mov r0, #5
b   _inf_loop

_svc_call_handler:
mov r0, #6
b   _inf_loop

_pend_sv_handler:
mov r0, #7
b   _inf_loop

_sys_tick_handler:
mov r0, #8
b   _inf_loop

_irq_handler:
mov r0, #9
b   _inf_loop

_inf_loop:
push {r7, lr}
mov r7, #0

_inf_loop_internal:
add r7, r7, #1
b   _inf_loop_internal

_usart2_handler:
push    {lr}
blx  _Z9SerialIntv
pop     {pc}


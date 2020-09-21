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

_reset_handler:
movw    fp, #0
movw    sp, #0
movw    sp, #0xfff0      // Set sp to 0x2001fff0
movt    sp, #0x2001
bl  main
b   _inf_loop

_nmi_handler:
mov r0, #1
b   _inf_loop

_hard_fault_handler:
mov r0, #2
b   _inf_loop

_mem_manage_handler:
mov r0, #3
b   _inf_loop

_bus_fault_handler:
mov r0, #4
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
add r1, r1, #1
b   _inf_loop


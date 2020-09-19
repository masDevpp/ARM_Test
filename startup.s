//.section .text

b   _reset_handler          // reset
b   _undefined_instruction_handler // undefined instruction
b   _software_int_handler   // softoware
b   _prefetch_abort_handler // prefetch abort
b   _data_abort_handler     // data abort
b   _nop_function           // not assigned
b   _irq_handler            // IRQ
b   _fiq_handler            // FIQ

_reset_handler:
movw    sp,  0xfff0      // Set sp to 0x2001fff0
movt    sp,  0x2001
bl  main
b   _nop_function

_undefined_instruction_handler:
b   _undefined_instruction_handler

_software_int_handler:
b   _software_int_handler

_prefetch_abort_handler:
b   _prefetch_abort_handler

_data_abort_handler:
b   _data_abort_handler

_nop_function:
b   _nop_function

_irq_handler:
b   _irq_handler

_fiq_handler:
b   _fiq_handler


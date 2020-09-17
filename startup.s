//.section .text

b   _reset_handler    // reset
b   _nop_function     // undefined
b   _nop_function     // softoware
b   _nop_function     // prefetch abort
b   _nop_function     // data abort
b   _nop_function     // not assigned
b   _nop_function     // IRQ
b   _nop_function     // FIQ

_reset_handler:
movw    sp,  0xfff0      // Set sp to 0x2001fff0
movt    sp,  0x2001
bl   main

_nop_function:
b   _nop_function

.end

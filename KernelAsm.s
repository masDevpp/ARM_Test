.global _setup_thread_stack 
.global _start_thread
.global _thread_switch
.global _stop_cpu

_setup_thread_stack:
// r0: pc
// r1: sp
// r2: Num of registers to clear
push    {r3-r4, lr}
mov     r3, r1
mov     r4, #0

_clear_stack:
// Clear r0-r7 area
str     r4, [r3]
add     r3, r3, #4
sub     r2, r2, #1
cmp     r2, #0
bne     _clear_stack

// Set Thumb bit for xpsr register
sub     r3, #4
movt    r4, #0x0100
str     r4, [r3]

// Store PC
sub     r3, #4
str     r0, [r3]

pop     {r3-r4, pc}

_start_thread:
// r0: pc
// r1: sp
mov     sp, r1
bx      r0

_thread_switch:
// lr not points return address but EXC_RETURN value, that is generated by CPU
push    {r0-r7}

// Get current and next thread number
ldr     r1, =_ZN6Kernel13CurrentThreadE
ldr     r1, [r1]
ldr     r2, =_ZN6Kernel10NextThreadE
ldr     r2, [r2]

// Get sp array address
ldr     r3, =_ZN6Kernel8ThreadSPE
ldr     r3, [r3]

// Store sp of current thread
mov     r4, r1
mov     r5, #4
mul     r4, r5
mov     r5, sp
str     r5, [r3, r4]

// Load sp of next thread
mov     r4, r2
mov     r5, #4
mul     r4, r5
ldr     r5, [r3, r4]
mov     sp, r5

// Update current thread number
ldr     r3, =_ZN6Kernel15NumberOfThreadsE
ldr     r3, [r3]

add     r1, r1, #1
cmp     r3, r1
bne     _update_current_thread_number
mov     r1, #0

_update_current_thread_number:
ldr     r4, =_ZN6Kernel13CurrentThreadE
str     r1, [r4]

// Update next thread number
add     r2, r2, #1
cmp     r3, r2
bne     _update_next_thread_number
mov     r2, #0

_update_next_thread_number:
ldr     r4, =_ZN6Kernel10NextThreadE
str     r2, [r4]

// Pop context of next thread
pop     {r0-r7}

// Load lr to pc
bx      lr

_stop_cpu:
bkpt

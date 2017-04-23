    .global main

format:
    .asciz "%llu"
main:
    movl A, %xmm0
    pushl %xmm0
    pushl $format
    call printf
    ret
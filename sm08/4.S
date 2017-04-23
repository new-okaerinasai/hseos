    .global main
    .text
main:
    movl $0, %ebx
    movl $0, %eax
read:
    addl %eax, %ebx
    jo fin_ovf
    call readi32
    jnc read

fin:
    movl %ebx, %eax
    call writei32
    call nl
    call finish

fin_ovf:
    sar $31, %ebx
    xorl $0x80000000, %ebx
    movl %ebx, %eax
    call writei32
    call nl
    call finish

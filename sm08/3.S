    .global main
    .text
main:
    call readi32
    cmpl $0, %eax
    movl %eax, %ebx
    movl %eax, %ecx
    je final0
    jl final
print:
    movl %ecx, %ebx
    movl %ecx, %eax
    call writei32
    call nl
    movl %ebx, %ecx
    loop print

    movl $0, %eax
    call writei32
    call nl
final:
    call finish
final0:
    call writei32
    call nl
    call finish

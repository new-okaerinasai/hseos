    .global main
    .text
main:
    movl $0, %eax
    movl $0, %esi
    movl $0, %edi
read:
    testl $1, %eax
    jz even
    jnz odd
odd:
    addl %eax, %esi
    jmp continue
even:
    addl %eax, %edi
    jmp continue
continue:
    call readi32
    jo read

    movl %esi, %eax
    call writei32
    call nl
    movl %edi, %eax
    call writei32
    call nl
    call finish
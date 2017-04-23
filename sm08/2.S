    .text
    .global process
    .global main

process:
    movl A, %eax
    imull B
    movl %eax, %ebx

    movl C, %eax
    imull D

    subl %eax, %ebx
    
    movl %ebx, R
    ret

main:
    call process
    call finish

data:
A:  .int 1
B:  .int 2
C:  .int 3
D:  .int 4
R:  .int

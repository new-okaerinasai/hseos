    .text
    .global process, A, B, C, D, R
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

    .data
A:  .int 0
B:  .int 0
C:  .int 0
D:  .int 0
R:  .int 0

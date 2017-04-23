        .data
        .align  16
        .global process, end_process, scanp, printp
process:
        pushl %ebx
        call l1
l1:     popl %ebx
        movl %ebx, %eax
        addl $A - l1, %eax
        pushl %eax
        movl %ebx, %eax
        addl $B - l1, %eax
        pushl %eax
        movl %ebx, %eax
        addl $str - l1, %eax
        pushl %eax
        movl %ebx, %eax
        addl $scanp - l1, %eax
        jmp *%eax


scanp:  call    scanf
        movl %ebx, %ecx
        addl $A - l1, %ecx

        movl (%ecx), %eax
        movl %ebx, %ecx
        addl $B - l1, %ecx
        addl (%ecx), %eax

        pushl %eax
        movl %ebx, %ecx
        addl $str2 - l1, %ecx
        pushl %ecx
        movl %ebx, %ecx
        addl $printp - l1, %ecx
        jmp *%ecx

printp: call    printf

        addl $20, %esp
        popl %ebx
        ret

str:    .asciz  "%d%d"
str2:   .asciz  "%d\n"
        .align  4
A:      .int    0
B:      .int    0
end_process:
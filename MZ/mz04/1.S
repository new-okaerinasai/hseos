    .global process
    .text

process:
    pushl %ebp
    movl %esp, %ebp
    movl A, %eax
    cmpl %eax, B
    jg AB
    jmp BA
AB: /* ACB, ABC, CAB*/
    movl C, %ecx
    cmpl B, %ecx
    jg ABC
    jmp AB_1
ABC: 
    movl B, %eax
    jmp end
AB_1: /*ACB, CAB */
    cmpl %ecx, A
    jg CAB
    jmp ACB


CAB:
    movl A, %eax
    jmp end
ACB:
    movl C, %eax
    jmp end

BA: /* BAC, BCA, CBA*/
    movl C, %ecx
    cmpl A, %ecx
    jg BAC
    jmp BA_1

BA_1: /* BCA, CBA*/
    cmpl %ecx, B
    jg CBA
    jmp BCA
CBA:
    movl B, %eax
    jmp end
BCA:
    movl C, %eax
    jmp end
BAC:
    movl A, %eax
    jmp end

end:
    movl %ebp, %esp
    popl %ebp
    ret
#include <asm/unistd_32.h>
        .global writeu32
        .text
divide:
        pushl %ebp
        movl %esp, %ebp

        subl $20, %esp
        movl $0, -4(%ebp)


while_a_greater_8:

        cmpl $8, 8(%ebp)
        jbe check
        
        movl 8(%ebp), %eax
        
        shrl $3, %eax
        movl %eax, -8(%ebp)

        movl 8(%ebp), %edx
        movl %edx, -12(%ebp)
        movl -8(%ebp), %eax
        shll $3, %eax
        subl %eax, -12(%ebp)

        movl -8(%ebp), %edx
        addl %edx, -4(%ebp)

        movl -8(%ebp), %eax
        shll $1, %eax
        movl %eax, 8(%ebp)
        movl -8(%ebp), %eax
        addl %eax, 8(%ebp)
        movl -12(%ebp), %eax
        addl %eax, 8(%ebp)

        jmp while_a_greater_8
check:

        cmpl $5, 8(%ebp)
        jge S
        jmp T
S:
        addl $1, -4(%ebp)
T:
        movl -4(%ebp), %eax
        shrl $1, %eax
        addl $20, %esp
        movl %ebp, %esp
        popl %ebp
        ret

writeu32:
        pushl %edi
        pushl %esi
        pushl %ebx
        pushl %ebp
        movl %esp, %ebp
        xorl %esi, %esi
        xorl %edi, %edi
        cmpl $0, %eax
        jne while_a_greater_0
        movl $'0', %eax
        call writechar
        jmp end

while_a_greater_0:
        cmpl $0, %eax
        je continue
        addl $1, %esi

        movl %eax, %ebx
        pushl %eax
        call divide
        add $4, %esp
        movl %eax, %edi
        movl $10, %ecx
        mull %ecx
        subl %eax, %ebx
        addl $'0', %ebx
        pushl %ebx
        movl %edi, %eax

        jmp while_a_greater_0

continue:
write:
        cmpl $0, %esi
        je end
        popl %eax
        call writechar
        subl $1, %esi
        jmp write
end:
        movl %ebp, %esp
        popl %ebp
        popl %ebx
        popl %esi
        popl %edi
        ret
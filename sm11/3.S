#include <asm/unistd_32.h>
        .global nextchar, readu32
        .global nc
        .text

readu32:
        pushl %edi
        pushl %esi
        xorl %esi, %esi
        xorl %edi, %edi
        subl $12, %esp
        movl $0, (%esp)
        movl $1, 4(%esp)
read:
        cmpl $1, (%esp)
        je passed
        cmpl $-1, nc
        je eof
        cmpl $32, nc
        jle call_read

passed:
        movl $1, (%esp)
        cmpl $-1, nc
        je end

        cmpl $'0', nc
        jl end
        cmpl $'9', nc
        jg end

        movl $0, 4(%esp)
        /* a*10 = a*5*2 = a*(4 + 1)*2 = (a*4 + a)*2 = ((a << 2) + a) << 1 */
        subl $'0', nc
        movl %esi, %ecx
        shll $2, %esi
        adcl $0, %edi
        addl %ecx, %esi
        adcl $0, %edi
        shll $1, %esi
        adcl $0, %edi
        addl nc, %esi
        adcl $0, %edi
        jmp call_read

end:
        cmpl $0, %edi
        jne fail

        cmpl $1, 4(%esp)
        je fail

        movl $1, %eax
        movl %esi, %edx
        jmp finish
fail:
        movl $-1, %eax
        jmp finish
eof:
        movl $0, %eax
finish:
        addl $12, %esp
        popl %esi
        popl %edi
        ret
call_read:
        call nextchar
        jmp read
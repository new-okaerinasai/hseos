#include <asm/unistd_32.h>
	.global _start


_start:
/*
lmao:
		cmpl $-1, %eax
		movl %eax, %ebx
		je end
		call writeu32
		movl %ebx, %eax
		addl $1, %eax
		jmp lmao*/
		movl $-1, %eax
		call writeu32
end:
		call flush
		movl $__NR_exit, %eax
		int $0x80


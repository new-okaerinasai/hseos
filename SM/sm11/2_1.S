		global _start
		extern readchar

_start:
		subl $4, %esp
		call readchar
		movl %eax, (%esp)
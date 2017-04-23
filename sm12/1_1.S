.data
.align 16
.global process
process:
pushl %ebp
movl %esp, %ebp
movl %ebp, %esp
popl %ebp
ret
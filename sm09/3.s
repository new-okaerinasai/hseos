	.file	"3.c"
	.globl	__asan_stack_malloc_1
	.section	.rodata
.LC0:
	.string	"1 32 5 1 a "
	.align 32
.LC1:
	.string	"%c\n"
	.zero	60
	.text
	.globl	main
	.type	main, @function
main:
.LASANPC0:
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x70,0x6
	.cfi_escape 0x10,0x7,0x2,0x75,0x7c
	.cfi_escape 0x10,0x6,0x2,0x75,0x78
	.cfi_escape 0x10,0x3,0x2,0x75,0x74
	subl	$104, %esp
	leal	-120(%ebp), %esi
	movl	%esi, %edi
	cmpl	$0, __asan_option_detect_stack_use_after_return
	je	.L1
	subl	$8, %esp
	pushl	%esi
	pushl	$96
	call	__asan_stack_malloc_1
	addl	$16, %esp
	movl	%eax, %esi
.L1:
	leal	96(%esi), %eax
	movl	$1102416563, (%esi)
	movl	$.LC0, 4(%esi)
	movl	$.LASANPC0, 8(%esi)
	movl	%esi, %ebx
	shrl	$3, %ebx
	movl	$-235802127, 536870912(%ebx)
	movl	$-185273339, 536870916(%ebx)
	movl	$-202116109, 536870920(%ebx)
	movl	%gs:20, %edx
	movl	%edx, -28(%ebp)
	xorl	%edx, %edx
	movl	$1868655980, -64(%eax)
	movb	$0, -60(%eax)
	movzbl	-64(%eax), %eax
	movsbl	%al, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	cmpl	%esi, %edi
	je	.L2
	movl	$1172321806, (%esi)
	movl	$-168430091, 536870912(%ebx)
	movl	$-168430091, 536870916(%ebx)
	movl	$-168430091, 536870920(%ebx)
	jmp	.L3
.L2:
	movl	$0, 536870912(%ebx)
	movl	$0, 536870916(%ebx)
	movl	$0, 536870920(%ebx)
.L3:
	movl	-28(%ebp), %ecx
	xorl	%gs:20, %ecx
	je	.L6
	call	__stack_chk_fail
.L6:
	leal	-16(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 32
.LC2:
	.string	"3.c"
	.zero	60
	.data
	.align 32
	.type	.Lubsan_data0, @object
	.size	.Lubsan_data0, 28
.Lubsan_data0:
	.long	.LC2
	.long	5
	.long	2
	.long	0
	.long	0
	.long	0
	.long	1
	.zero	36
	.section	.rodata
.LC3:
	.string	"*.Lubsan_data0"
.LC4:
	.string	"*.LC1"
.LC5:
	.string	"*.LC2"
	.data
	.align 32
	.type	.LASAN0, @object
	.size	.LASAN0, 84
.LASAN0:
	.long	.Lubsan_data0
	.long	28
	.long	64
	.long	.LC3
	.long	.LC2
	.long	0
	.long	0
	.long	.LC1
	.long	4
	.long	64
	.long	.LC4
	.long	.LC2
	.long	0
	.long	0
	.long	.LC2
	.long	4
	.long	64
	.long	.LC5
	.long	.LC2
	.long	0
	.long	0
	.text
	.type	_GLOBAL__sub_D_00099_0_main, @function
_GLOBAL__sub_D_00099_0_main:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$3
	pushl	$.LASAN0
	call	__asan_unregister_globals
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_GLOBAL__sub_D_00099_0_main, .-_GLOBAL__sub_D_00099_0_main
	.section	.fini_array.00099,"aw"
	.align 4
	.long	_GLOBAL__sub_D_00099_0_main
	.text
	.type	_GLOBAL__sub_I_00099_1_main, @function
_GLOBAL__sub_I_00099_1_main:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	call	__asan_init_v4
	subl	$8, %esp
	pushl	$3
	pushl	$.LASAN0
	call	__asan_register_globals
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_GLOBAL__sub_I_00099_1_main, .-_GLOBAL__sub_I_00099_1_main
	.section	.init_array.00099,"aw"
	.align 4
	.long	_GLOBAL__sub_I_00099_1_main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits

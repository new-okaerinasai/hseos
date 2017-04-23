	.data
A:  .int 1
B:  .int 1

	.text
	.global main

main:
	call print_fib
	ret
    .text
    .global hijack_rand, my_rand
    .data
addr: .int 0
var: .int 0

my_rand:
    andl $0x0000FFFF, var
    movl var, %ecx
    pushl %ecx
    call *addr
    popl %ecx
    movl %eax, var
    movl %ecx, %eax
    ret

hijack_rand:
    call rand
    movl %eax, var
    movl $rand, %eax
    movl 2(%eax), %eax
    movl (%eax), %ecx
    movl %ecx, addr
    
    movl $my_rand, (%eax)

    ret

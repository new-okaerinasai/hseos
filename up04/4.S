    .global list_del
    .text

list_del:
    pushl %ebp
    movl %esp, %ebp
    subl $12, %esp
check_null:
    movl 8(%ebp), %eax
    cmpl $0, %eax
    je end

    movl 8(%ebp), %eax
    movl %eax, -4(%ebp)
    movl 8(%ebp), %eax
    movl %eax, -8(%ebp)
    /* current = -4(%ebp), previous = -8(%ebp) */

while_current_not_null:   
    movl -4(%ebp), %eax
    cmpl $0, %eax
    je if_head_value_is_value
if_current_value_is_value:
    movl -4(%ebp), %eax
    movzbl (%eax), %eax
    movsbl %al, %eax
    cmpl %eax, 12(%ebp)
    je kick
    jne continue
kick:
    movl -4(%ebp), %eax
    movl 4(%eax), %edx
    movl -8(%ebp), %eax
    movl %edx, 4(%eax)
    movl -4(%ebp), %eax
    movl 4(%eax), %eax
    movl %eax, -4(%ebp)
    jmp while_current_not_null
continue:
    movl -4(%ebp), %eax
    movl %eax, -8(%ebp)
    movl -4(%ebp), %eax
    movl 4(%eax), %eax
    movl %eax, -4(%ebp)
    jmp while_current_not_null
if_head_value_is_value:
    movl 8(%ebp), %eax
    movzbl (%eax), %eax
    movsbl %al, %eax
    cmpl %eax, 12(%ebp)
    jne end
    movl 8(%ebp), %eax
    movl 4(%eax), %eax
    movl %eax, 8(%ebp)
end:
    movl 8(%ebp), %eax
    movl %ebp, %esp
    popl %ebp
    ret
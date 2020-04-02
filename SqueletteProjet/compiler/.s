.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $3, -4(%rbp)
	movl $2, -8(%rbp)
	movl -4(%rbp), %eax
	cmpl  %eax, -8(%rbp)
	setae %dl
	mov %dl, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp)
	movl -16(%rbp), %eax
	popq %rbp
	ret

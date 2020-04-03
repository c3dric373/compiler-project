.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $6, -4(%rbp)
	movl $6, -8(%rbp)
	movl -4(%rbp) , %eax
	and -8(%rbp), %eax
	movl %eax, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp)
	movl -16(%rbp), %eax
	popq %rbp
	ret

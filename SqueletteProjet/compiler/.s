.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $97, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -2(%rbp)
	movl $3, -6(%rbp)
	movl -6(%rbp) , %eax
	addl -2(%rbp), %eax
	movl %eax, -10(%rbp)
	movl -10(%rbp), %eax
	movl %eax , -14(%rbp)
	movl -14(%rbp), %eax
	popq %rbp
	ret

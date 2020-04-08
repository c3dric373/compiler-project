.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $10, %rsp
	movb $97, -1(%rbp)
	movl $22, -2(%rbp)
	movl -1(%rbp) , %eax
	addl -2(%rbp), %eax # b + c
	movl %eax, -10(%rbp)
	addq $10, %rsp
	popq %rbp
	ret

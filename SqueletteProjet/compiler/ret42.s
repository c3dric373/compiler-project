.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $3, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -8(%rbp)
	movl -8(%rbp), %eax
	popq %rbp
	ret

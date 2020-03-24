.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl $6, -8(%rbp)
	movl $7, -12(%rbp)
	movl -8(%rbp), %eax
	popq %rbp
	ret

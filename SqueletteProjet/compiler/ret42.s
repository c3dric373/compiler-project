.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	movl $42, -4(%rbp)
	movl -4(%rbp), %eax
	addq $8, %rsp
	popq %rbp
	ret

f:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movl %edi, -8(%rbp)# write arg i
	movl $1, -12(%rbp)
	movl -8(%rbp) , %eax
	addl -12(%rbp), %eax # i + !tmp12
	movl %eax, -16(%rbp)
	movl -16(%rbp), %eax
	movl %eax , -8(%rbp) # i
	movl -8(%rbp), %eax
	addq $16, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl -8(%rbp), %edi # fct param a
	call f
	movl %eax, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp) # b
	movl -16(%rbp), %eax
	addq $16, %rsp
	popq %rbp
	ret

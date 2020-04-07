test:
	pushq %rbp
	movq %rsp, %rbp
	subq $24, %rsp
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # d
	movl $2, -12(%rbp)
	movl -8(%rbp) , %eax
	addl -12(%rbp), %eax # d + !tmp12
	movl %eax, -16(%rbp)
	movl -16(%rbp), %eax
	movl %eax , -20(%rbp) # f
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp) # g
	addq $24, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl -8(%rbp), %eax
	movl %eax , -12(%rbp) # fct param -12(%rbp)
	movl -8(%rbp), %eax
	addq $8, %rsp
	popq %rbp
	ret

test:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movl 16(%rbp), %eax# get arg c
	movl %eax , -4(%rbp)  # write argc
	movl 24(%rbp), %eax# get arg b
	movl %eax , -8(%rbp)  # write argb
	movl -4(%rbp) , %eax
	addl -8(%rbp), %eax # c + b
	movl %eax, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp) # g
	movl -16(%rbp), %eax
	addq $16, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $20, %rsp
	movl $20, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $4, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp) # f
	movl -8(%rbp), %eax
	movl %eax , -20(%rbp) # fct param -20(%rbp)
	movl -16(%rbp), %eax
	movl %eax , -24(%rbp) # fct param -24(%rbp)
	call test
	movl %eax, %eax
	movl %eax , -20(%rbp) # b
	movl -20(%rbp), %eax
	addq $20, %rsp
	popq %rbp
	ret

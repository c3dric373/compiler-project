f:
	pushq %rbp
	movq %rsp, %rbp
	subq $12, %rsp
	movl %edi, -4(%rbp)# write arg i
	movl %esi, -8(%rbp)# write arg c
	movl $2, -12(%rbp)
	movl -12(%rbp), %eax
	addq $12, %rsp
	popq %rbp
	ret
h:
	pushq %rbp
	movq %rsp, %rbp
	subq $12, %rsp
	movl %edi, -4(%rbp)# write arg i
	movl %esi, -8(%rbp)# write arg c
	movl -4(%rbp), %edi # fct param i
	movl -8(%rbp), %esi # fct param c
	call f
	movl %eax, %eax
	movl %eax , -8(%rbp) # c
	movl -8(%rbp) , %eax
	addl -4(%rbp), %eax # c + i
	movl %eax, -12(%rbp)
	movl -12(%rbp), %eax
	addq $12, %rsp
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
	movl $0, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp) # b
	movl -8(%rbp), %edi # fct param a
	movl -16(%rbp), %esi # fct param b
	call h
	movl %eax, %eax
	movl %eax , -16(%rbp) # b
	movl -16(%rbp), %eax
	addq $16, %rsp
	popq %rbp
	ret

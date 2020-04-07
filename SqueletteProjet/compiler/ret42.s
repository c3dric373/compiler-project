test:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	movl %ebx, %eax
	movl %eax , -8(%rbp) # g
	movl -8(%rbp), %eax
	addq $8, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $12, %rsp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl -8(%rbp), %eax
	movl %eax , %ebx # fct param -12(%rbp)
	call test
	movl %eax, %eax
	movl %eax , -12(%rbp) # b
	movl -12(%rbp), %eax
	addq $12, %rsp
	popq %rbp
	ret

test:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # d
	addq $8, %rsp
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
	movl %eax , 100(%rbp) # -12(%rbp)
	movl -8(%rbp), %eax
	addq $8, %rsp
	popq %rbp
	ret

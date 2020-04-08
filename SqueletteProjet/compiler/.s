f:
	pushq %rbp
	movq %rsp, %rbp
	subq $12, %rsp
	movl %edi, -4(%rbp)# write arg i
	movl $1, -8(%rbp)
	movl -4(%rbp) , %eax
	addl -8(%rbp), %eax # i + !tmp8
	movl %eax, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -4(%rbp) # i
	movl -4(%rbp), %eax
	addq $12, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl -8(%rbp), %edi # fct param a
	call f
	movl 100(%rbp), %eax
	addq $8, %rsp
	popq %rbp
	ret

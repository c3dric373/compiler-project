.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $0, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -4(%rbp) # 0a
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # 1a
	movl $3, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -12(%rbp) # 2a
	movl $4, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -16(%rbp) # 3a
	movl -12(%rbp), %eax
	popq %rbp
	ret

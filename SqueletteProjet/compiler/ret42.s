.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
.L0: 
	movl $5, -12(%rbp)
	movl -12(%rbp), %eax
	cmp  %eax, -8(%rbp)
	setb %dl
	movzbl %dl, %eax
	movl %eax, -16(%rbp)
	cmpl $1, -16(%rbp)
	je .L1
	jmp .L2
.L1: 
	movl $1, -20(%rbp)
	movl -8(%rbp) , %eax
	addl -20(%rbp), %eax
	movl %eax, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -8(%rbp)
	 jmp .L0
.L2: 
	movl -8(%rbp), %eax
	popq %rbp
	ret

.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $9, -20(%rbp)
	movl -20(%rbp), %eax
	cmp  %eax, -8(%rbp)
	setbe %dl
	movzbl %dl, %eax
	movl %eax, -24(%rbp)
	cmpl $1, -24(%rbp)
	je .L0
	jmp .L1
.L0: 
	movl $2, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -16(%rbp)
.L1: 
	movl -16(%rbp), %eax
	popq %rbp
	ret

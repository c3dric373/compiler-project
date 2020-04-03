.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $3, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $2, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp)
	movl $7, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp)
	movl $4, -28(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -28(%rbp)
	sete %dl
	movzbl %dl, %eax
	movl %eax, -32(%rbp)
	cmpl $1, -32(%rbp)
	je .L0
	jmp .L1
.L0: 
	movl $2, -36(%rbp)
	movl -36(%rbp), %eax
	movl %eax , -24(%rbp)
	 jmp .L2
.L1: 
	movl $4, -40(%rbp)
	movl -40(%rbp), %eax
	movl %eax , -24(%rbp)
.L2: 
	movl $5, -44(%rbp)
	movl -44(%rbp), %eax
	movl %eax , -48(%rbp)
	movl -24(%rbp), %eax
	popq %rbp
	ret

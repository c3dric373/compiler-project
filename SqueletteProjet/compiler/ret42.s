.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $3, -4(%rbp)
	movl $3, -8(%rbp)
	movl -4(%rbp), %eax
	cmpl  %eax, -8(%rbp)
	sete %dl
	movzbl %dl, %eax
	movl %eax, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp)
	movl $2, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp)
	movl $7, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -32(%rbp)
	movl $2, -36(%rbp)
	movl -24(%rbp), %eax
	cmpl  %eax, -36(%rbp)
	sete %dl
	movzbl %dl, %eax
	movl %eax, -40(%rbp)
	movl -16(%rbp), %eax
	cmpl  %eax, -40(%rbp)
	sete %dl
	movzbl %dl, %eax
	movl %eax, -44(%rbp)
	cmpl $1, -44(%rbp)
	je .L0
	jmp .L1
.L0: 
	movl $2, -48(%rbp)
	movl -48(%rbp), %eax
	movl %eax , -32(%rbp)
.L1: 
	movl -32(%rbp), %eax
	popq %rbp
	ret

.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $5, -20(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -20(%rbp)
	sete %dl # a==!tmp20
	movzbl %dl, %eax
	movl %eax, -24(%rbp)
	cmpl $1, -24(%rbp)
	je .L1
	jmp .L2
.L1: 
	movl $3, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -32(%rbp) # d
	 jmp .L0
.L2: 
	movl $4, -36(%rbp)
	movl -36(%rbp), %eax
	movl %eax , -12(%rbp) # b
.L0: 
	movl -1(%rbp), %eax
	popq %rbp
	ret

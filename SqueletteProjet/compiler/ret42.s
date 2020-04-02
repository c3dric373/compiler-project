.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $2, -20(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -20(%rbp)
	jne .L0
	jmp .L1
.L0: 
	movl $2, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -16(%rbp)
	movl $1, -28(%rbp)
	movl -16(%rbp), %eax
	cmpl  %eax, -28(%rbp)
	jne .L2
	jmp .L3
.L2: 
	movl $3, -32(%rbp)
	movl -32(%rbp), %eax
	movl %eax , -12(%rbp)
.L3: 
	movl $5, -36(%rbp)
	movl -36(%rbp), %eax
	movl %eax , -40(%rbp)
.L1: 
	movl -16(%rbp), %eax
	popq %rbp
	ret

.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $5, -20(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -20(%rbp)
	jne .L1
	jmp .L0
.L0: 
	movl $2, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -16(%rbp)
	movl $2, -28(%rbp)
	movl -16(%rbp), %eax
	cmpl  %eax, -28(%rbp)
	jne .L3
	jmp .L2
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

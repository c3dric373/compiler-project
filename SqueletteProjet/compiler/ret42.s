.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
.L0: 
	movl $0, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp) # i
.L1: 
	movl $5, -20(%rbp)
	movl -20(%rbp), %eax
	cmp  %eax, -16(%rbp)
	setb %dl # i<!tmp20
	movzbl %dl, %eax
	movl %eax, -24(%rbp)
	cmpl $1, -1(%rbp)
	je .L2
	jmp .L3
.L2: 
	movl $1, -28(%rbp)
	movl -8(%rbp) , %eax
	addl -28(%rbp), %eax # a * !tmp28
	movl %eax, -32(%rbp)
	movl -32(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $1, -36(%rbp)
	movl -16(%rbp) , %eax
	addl -36(%rbp), %eax # i * !tmp36
	movl %eax, -40(%rbp)
	movl -40(%rbp), %eax
	movl %eax , -16(%rbp) # i
	 jmp .L1
.L3: 
	movl -8(%rbp), %eax
	popq %rbp
	ret

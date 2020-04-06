.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $0, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $0, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp) # c
.L0: 
	movl $0, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp) # i
.L1: 
	movl $10, -28(%rbp)
	movl -28(%rbp), %eax
	cmp  %eax, -24(%rbp)
	setb %dl # i<!tmp28
	movzbl %dl, %eax
	movl %eax, -32(%rbp)
	cmpl $1, -32(%rbp)
	je .L2
	jmp .L3
.L2: 
.L4: 
	movl $3, -36(%rbp)
	movl -36(%rbp), %eax
	cmp  %eax, -8(%rbp)
	seta %dl # a>!tmp36
	movzbl %dl, %eax
	movl %eax, -40(%rbp)
	cmpl $1, -40(%rbp)
	je .L5
	jmp .L6
.L5: 
	movl -8(%rbp) , %eax
	addl -16(%rbp), %eax # a + c
	movl %eax, -44(%rbp)
	movl -44(%rbp), %eax
	movl %eax , -8(%rbp) # a
	 jmp .L4
.L6: 
	movl $1, -48(%rbp)
	movl -16(%rbp) , %eax
	addl -48(%rbp), %eax # c + !tmp48
	movl %eax, -52(%rbp)
	movl -52(%rbp), %eax
	movl %eax , -16(%rbp) # c
	movl $1, -56(%rbp)
	movl -24(%rbp) , %eax
	addl -56(%rbp), %eax # i + !tmp56
	movl %eax, -60(%rbp)
	movl -60(%rbp), %eax
	movl %eax , -24(%rbp) # i
	 jmp .L1
.L3: 
	movl -8(%rbp) , %eax
	addl -16(%rbp), %eax # a + c
	movl %eax, -64(%rbp)
	popq %rbp
	ret

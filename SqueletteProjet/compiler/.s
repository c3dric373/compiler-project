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
.L0: 
	movl $3, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp)
.L1: 
	movl $4, -28(%rbp)
	movl -24(%rbp), %eax
	cmpl  %eax, -28(%rbp)
	sete %dl
	movzbl %dl, %eax
	movl %eax, -32(%rbp)
	cmpl $1, -32(%rbp)
	je .L3
	jmp .L4
.L3: 
	movl $5, -36(%rbp)
	movl -36(%rbp), %eax
	movl %eax , -40(%rbp)
	movl -40(%rbp), %eax
	movl %eax , -16(%rbp)
	 jmp .L2
.L4: 
	movl $3, -44(%rbp)
	movl -44(%rbp), %eax
	movl %eax , -48(%rbp)
.L5: 
	movl $1, -52(%rbp)
	movl -52(%rbp), %eax
	cmp  %eax, -48(%rbp)
	seta %dl
	movzbl %dl, %eax
	movl %eax, -56(%rbp)
	cmpl $1, -56(%rbp)
	je .L6
	jmp .L7
.L6: 
	movl $2, -60(%rbp)
	movl -60(%rbp), %eax
	movl %eax , -64(%rbp)
	movl -16(%rbp) , %eax
	addl -64(%rbp), %eax
	movl %eax, -68(%rbp)
	movl -68(%rbp), %eax
	movl %eax , -16(%rbp)
	 jmp .L5
.L7: 
.L2: 
	movl -16(%rbp), %eax
	popq %rbp
	ret

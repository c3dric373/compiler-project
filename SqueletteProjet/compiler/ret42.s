.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $3, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $2, -12(%rbp)
	movl $3, -16(%rbp)
	movl -16(%rbp), %eax
	cmp  %eax, -12(%rbp)
	seta %dl # !tmp12>!tmp16
	movzbl %dl, %eax
	movl %eax, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp) # c
.L0: 
	movl -8(%rbp) , %eax
	addl -24(%rbp), %eax # a * c
	movl %eax, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -32(%rbp) # d
.L1: 
	movl $4, -36(%rbp)
	movl -32(%rbp), %eax
	cmpl  %eax, -36(%rbp)
	sete %dl # d==!tmp36
	movzbl %dl, %eax
	movl %eax, -40(%rbp)
	cmpl $1, -40(%rbp)
	je .L3
	jmp .L4
.L3: 
	movl $5, -44(%rbp)
	movl -44(%rbp), %eax
	movl %eax , -48(%rbp) # f
	movl $1, -52(%rbp)
	movl -48(%rbp) , %eax
	subl -52(%rbp), %eax# f - !tmp52
	movl %eax, -56(%rbp)
	movl -56(%rbp), %eax
	movl %eax , -24(%rbp) # c
	 jmp .L2
.L4: 
	movl $6, -60(%rbp)
	movl -60(%rbp), %eax
	movl %eax , -64(%rbp) # f
.L5: 
	movl $1, -68(%rbp)
	movl -68(%rbp), %eax
	cmp  %eax, -64(%rbp)
	seta %dl # f>!tmp68
	movzbl %dl, %eax
	movl %eax, -72(%rbp)
	cmpl $1, -72(%rbp)
	je .L6
	jmp .L7
.L6: 
	movl $2, -76(%rbp)
	movl $1, -80(%rbp)
	movl -76(%rbp) , %eax
	subl -80(%rbp), %eax# !tmp76 - !tmp80
	movl %eax, -84(%rbp)
	movl -84(%rbp), %eax
	movl %eax , -88(%rbp) # z
	movl -24(%rbp) , %eax
	addl -88(%rbp), %eax # c * z
	movl %eax, -92(%rbp)
	movl -92(%rbp) , %eax
	addl -32(%rbp), %eax # !tmp92 * d
	movl %eax, -96(%rbp)
	movl -96(%rbp), %eax
	movl %eax , -24(%rbp) # c
	movl $2, -100(%rbp)
	movl -64(%rbp) , %eax
	imull -100(%rbp), %eax # f * !tmp100
	movl %eax, -104(%rbp)
	movl -104(%rbp), %eax
	movl %eax , -64(%rbp) # f
	movl $1, -108(%rbp)
	movl -108(%rbp), %eax
	movl %eax , -32(%rbp) # d
	 jmp .L5
.L7: 
.L2: 
	movl -24(%rbp), %eax
	popq %rbp
	ret

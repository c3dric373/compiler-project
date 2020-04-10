.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $120, %rsp
	movl $20, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $4, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp) # b
	movl $9, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp) # c
	movl -24(%rbp) , %eax
	imull -16(%rbp), %eax # c * b
	movl %eax, -28(%rbp)
	movl -28(%rbp) , %eax
	subl -8(%rbp), %eax# !tmp28 - a
	movl %eax, -32(%rbp)
	movl -32(%rbp), %eax
	movl %eax , -36(%rbp) # d
	movl $4, -40(%rbp)
	movl -36(%rbp) , %eax
	imull -40(%rbp), %eax # d * !tmp40
	movl %eax, -44(%rbp)
	movl -44(%rbp), %eax
	movl %eax , -48(%rbp) # e
	movl -48(%rbp), %eax
	cmp  %eax, -16(%rbp)
	seta %dl # b>e
	movzbl %dl, %eax
	movl %eax, -52(%rbp)
	movl -8(%rbp), %eax
	cmp  %eax, -36(%rbp)
	setbe %dl # d<=a
	movzbl %dl, %eax
	movl %eax, -56(%rbp)
	movl -52(%rbp) , %eax
	or -56(%rbp), %eax # !tmp52 or!tmp56
	movl %eax, -60(%rbp)
	movl -60(%rbp), %eax
	movl %eax , -64(%rbp) # f
	movl -16(%rbp), %eax
	cmp  %eax, -24(%rbp)
	setb %dl # c<b
	movzbl %dl, %eax
	movl %eax, -68(%rbp)
	movl -8(%rbp), %eax
	cmp  %eax, -48(%rbp)
	seta %dl # e>a
	movzbl %dl, %eax
	movl %eax, -72(%rbp)
	movl -68(%rbp) , %eax
	imull -72(%rbp), %eax # !tmp68 * !tmp72
	movl %eax, -76(%rbp)
	movl -76(%rbp) , %eax
	imull -8(%rbp), %eax # !tmp76 * a
	movl %eax, -80(%rbp)
	movl -80(%rbp), %eax
	movl %eax , -84(%rbp) # g
	movl $125, -88(%rbp)
	movl -88(%rbp), %eax
	movl %eax , -92(%rbp) # m
	movl -8(%rbp) , %eax
	addl -16(%rbp), %eax # a + b
	movl %eax, -96(%rbp)
	cmpl $1, -96(%rbp)
	je .Lmain0
	jmp .Lmain1
.Lmain0: 
	movl -16(%rbp), %eax
	cmpl  %eax, -24(%rbp)
	sete %dl # b==c
	movzbl %dl, %eax
	movl %eax, -100(%rbp)
	movl -48(%rbp) , %eax
	and -8(%rbp), %eax # e and a
	movl %eax, -104(%rbp)
	movl -100(%rbp) , %eax
	imull -104(%rbp), %eax # !tmp100 * !tmp104
	movl %eax, -108(%rbp)
	movl -108(%rbp) , %eax
	addl -8(%rbp), %eax # !tmp108 + a
	movl %eax, -112(%rbp)
	movl -112(%rbp), %eax
	movl %eax , -92(%rbp) # m
	movl $78, -116(%rbp)
	movl -116(%rbp), %eax
	movl %eax , -120(%rbp) # w
.Lmain1: 
	movl -92(%rbp), %eax
	 jmp .main_ret
.main_ret:
	addq $120, %rsp
	popq %rbp
	ret

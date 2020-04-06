.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movb $97, -15(%rbp)
	movl -15(%rbp), %eax
	movb %al , -12(%rbp) # 11b
	movl $4, -19(%rbp)
	movl -19(%rbp), %eax
	movb %al , -10(%rbp) # 9b
	movb $98, -32(%rbp)
	movl -32(%rbp), %eax
	movl %eax , -23(%rbp) # 0a
	movl $2, -36(%rbp)
	movl -36(%rbp) , %eax
	addl -23(%rbp), %eax # !tmp36 + 0a
	movl %eax, -40(%rbp)
	movl -40(%rbp), %eax
	movl %eax , -27(%rbp) # 1a
	movl $2, -44(%rbp)
	movl -44(%rbp) , %eax
	imull -23(%rbp), %eax # !tmp44 * 0a
	movl %eax, -48(%rbp)
	movl $12, -52(%rbp)
	movl -52(%rbp) , %eax
	imull -10(%rbp), %eax # !tmp52 * 9b
	movl %eax, -56(%rbp)
	movl -48(%rbp) , %eax
	addl -56(%rbp), %eax # !tmp48 + !tmp56
	movl %eax, -60(%rbp)
	movl -60(%rbp), %eax
	movl %eax , -31(%rbp) # 2a
	movl $2, -64(%rbp)
	movl -64(%rbp) , %eax
	imull -27(%rbp), %eax # !tmp64 * 1a
	movl %eax, -68(%rbp)
	movl $4, -72(%rbp)
	movl -72(%rbp) , %eax
	imull -10(%rbp), %eax # !tmp72 * 9b
	movl %eax, -76(%rbp)
	movl -68(%rbp) , %eax
	subl -76(%rbp), %eax# !tmp68 - !tmp76
	movl %eax, -80(%rbp)
	movl -80(%rbp) , %eax
	addl -12(%rbp), %eax # !tmp80 + 11b
	movl %eax, -84(%rbp)
	popq %rbp
	ret

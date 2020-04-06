.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $1, -7(%rbp)
	movl -7(%rbp), %eax
	movl %eax , -1(%rbp) # 0a
	movl $2, -11(%rbp)
	movl -11(%rbp) , %eax
	addl -1(%rbp), %eax # !tmp11 + 0a
	movl %eax, -15(%rbp)
	movl -15(%rbp), %eax
	movl %eax , -2(%rbp) # 1a
	movl $2, -19(%rbp)
	movl -19(%rbp) , %eax
	imull -1(%rbp), %eax # !tmp19 * 0a
	movl %eax, -23(%rbp)
	movl $12, -27(%rbp)
	movl -27(%rbp) , %eax
	imull -2(%rbp), %eax # !tmp27 * 1a
	movl %eax, -31(%rbp)
	movl -23(%rbp) , %eax
	addl -31(%rbp), %eax # !tmp23 + !tmp31
	movl %eax, -35(%rbp)
	movl -35(%rbp), %eax
	movl %eax , -3(%rbp) # 2a
	movl -1(%rbp) , %eax
	addl -2(%rbp), %eax # 0a + 1a
	movl %eax, -39(%rbp)
	popq %rbp
	ret

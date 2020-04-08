.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $6, %rsp
	movb $97, -1(%rbp)
	movb $98, -2(%rbp)
	movb $101, -3(%rbp)
	movzbl -2(%rbp), %eax
	cmpb  %al, -1(%rbp)
	setbe %dl # a<=b
	movzbl %dl, %eax
	movl %eax, -4(%rbp)
	movzbl -3(%rbp), %eax
	cmpb  %al, -4(%rbp)
	setbe %dl # d<=c
	movzbl %dl, %eax
	movl %eax, -5(%rbp)
	movl -5(%rbp) , %eax
	addl -4(%rbp), %eax # e + d
	movl %eax, -6(%rbp)
	movl -6(%rbp), %eax
	addq $6, %rsp
	popq %rbp
	ret

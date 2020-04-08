.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $9, %rsp
	movb $97, -1(%rbp)
	movb $98, -2(%rbp)
	movzbl -2(%rbp), %eax
	cmpb  %al, -1(%rbp)
	setbe %dl # a<=b
	movzbl %dl, %eax
	movb %al, -3(%rbp)
	movzbl -2(%rbp), %eax
	cmpb  %al, -3(%rbp)
	setbe %dl # e<=b
	movzbl %dl, %eax
	movb %al, -4(%rbp)
	movl -3(%rbp) , %eax
	addl -2(%rbp), %eax # e + b
	movl %eax, -9(%rbp)
	movl -9(%rbp) , %eax
	addl -4(%rbp), %eax # !tmp9 + l
	movl %eax, -5(%rbp)
	movl -5(%rbp), %eax
	addq $9, %rsp
	popq %rbp
	ret

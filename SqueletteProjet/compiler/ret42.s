.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $2, %rsp
	call getchar
	movl %eax, -2(%rbp)
	movl -2(%rbp), %eax
	movb %al , -1(%rbp) # c
	movsbl -1(%rbp), %eax
	movl %eax, %edi
	call putchar
	movl -1(%rbp), %eax
	addq $2, %rsp
	popq %rbp
	ret

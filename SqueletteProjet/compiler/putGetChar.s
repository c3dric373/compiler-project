.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $2, %rsp
	call getchar
	movl %eax, -1(%rbp)
	movl -1(%rbp), %eax
	movb %al , -2(%rbp) # a
	movsbl -2(%rbp), %eax
	movl %eax, %edi
	call putchar
	movl -2(%rbp), %eax
	 jmp .main_ret
.main_ret:
	addq $2, %rsp
	popq %rbp
	ret

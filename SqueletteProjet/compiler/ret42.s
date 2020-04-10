.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $23, %rsp
	movl $8, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movb $102, -9(%rbp)
	movl -9(%rbp), %eax
	movl %eax , -13(%rbp) # b
	movsbl -13(%rbp), %eax
	movl %eax, %edi
	call putchar
	movl $4, -18(%rbp)
	movl -18(%rbp), %eax
	movl %eax , -22(%rbp) # n
	call getchar
	movl %eax, -23(%rbp)
	movl -23(%rbp), %eax
	movb %al , -14(%rbp) # x
	movl -14(%rbp), %eax
	 jmp .main_ret
.main_ret:
	addq $23, %rsp
	popq %rbp
	ret

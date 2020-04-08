f:
	pushq %rbp
	movq %rsp, %rbp
	subq $29, %rsp
	movl %edi, -8(%rbp)# write arg i
	movl %esi, %eax# relocate because arg is a char: c
	movb %al, -9(%rbp)# write arg c
	movl %edx, -13(%rbp)# write arg b
	movl %ecx, -17(%rbp)# write arg e
	movl %r8d, -21(%rbp)# write arg f
	movl %r9d, -25(%rbp)# write arg h
	movl -4(%rbp), %eax
	movl %eax , -29(%rbp) # carre
	movl -29(%rbp), %eax
	addq $29, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $10, %rsp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movb $102, -9(%rbp)
	movl -9(%rbp), %eax
	movb %al , -10(%rbp) # b
	movl -8(%rbp), %eax
	movl %eax, -30(%rbp) # fct param a
	movl -8(%rbp), %edi # fct param a
	movl -10(%rbp), %esi # fct param b
	movl -8(%rbp), %edx # fct param a
	movl -8(%rbp), %ecx # fct param a
	movl -8(%rbp), %r8d # fct param a
	movl -8(%rbp), %r9d # fct param a
	call f
	movl %eax, %eax
	movb %al , -10(%rbp) # b
	movl -10(%rbp), %eax
	addq $10, %rsp
	popq %rbp
	ret

<<<<<<< HEAD
factorielle:
	pushq %rbp
	movq %rsp, %rbp
	subq $21, %rsp
	movl %edi, -8(%rbp)# write arg i
	movl %esi, %eax# relocate because arg is a char: c
	movb %al, -9(%rbp)# write arg c
	movl $1, -13(%rbp)
	movl -8(%rbp) , %eax
	addl -13(%rbp), %eax # i + !tmp13
	movl %eax, -17(%rbp)
	movl -17(%rbp), %eax
	movl %eax , -8(%rbp) # i
	movl -9(%rbp) , %eax
	addl -8(%rbp), %eax # c + i
	movl %eax, -21(%rbp)
	movl -21(%rbp), %eax
	addq $21, %rsp
	popq %rbp
	ret
g:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movl %edi, -8(%rbp)# write arg j
	movl $2, -12(%rbp)
	movl -8(%rbp) , %eax
	addl -12(%rbp), %eax # j + !tmp12
	movl %eax, -16(%rbp)
	movl -16(%rbp), %eax
	addq $16, %rsp
	popq %rbp
	ret
h:
	pushq %rbp
	movq %rsp, %rbp
	subq $46, %rsp
	movl %edi, -8(%rbp)# write arg i
	movl %esi, %eax# relocate because arg is a char: c
	movb %al, -9(%rbp)# write arg c
	movl %edx, -13(%rbp)# write arg z
	movl %ecx, -17(%rbp)# write arg x
	movl %r8d, -21(%rbp)# write arg y
	movl %r9d, %eax# relocate because arg is a char: l
	movb %al, -22(%rbp)# write arg l
	movl -8(%rbp), %edi # fct param i
	movl -9(%rbp), %esi # fct param c
	call f
	movl %eax, -26(%rbp)
	movl -26(%rbp), %eax
	movb %al , -9(%rbp) # c
	movl -9(%rbp), %edi # fct param c
	call g
	movl %eax, -30(%rbp)
	movl -30(%rbp), %eax
	movl %eax , -34(%rbp) # d
	movl -9(%rbp) , %eax
	addl -8(%rbp), %eax # c + i
	movl %eax, -38(%rbp)
	movl $3, -42(%rbp)
	movl -38(%rbp) , %eax
	addl -42(%rbp), %eax # !tmp38 + !tmp42
	movl %eax, -46(%rbp)
	movl -46(%rbp), %eax
	addq $46, %rsp
	popq %rbp
	ret
=======
>>>>>>> develop
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
<<<<<<< HEAD
	subq $41, %rsp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movb $99, -21(%rbp)
	movl -21(%rbp), %eax
	movb %al , -22(%rbp) # l
	movb $102, -23(%rbp)
	movl $2, -27(%rbp)
	movl -23(%rbp) , %eax
	addl -27(%rbp), %eax # !tmp23 + !tmp27
	movl %eax, -31(%rbp)
	movb $97, -32(%rbp)
	movl -31(%rbp) , %eax
	addl -32(%rbp), %eax # !tmp31 + !tmp32
	movl %eax, -36(%rbp)
	movl -36(%rbp), %eax
	movb %al , -37(%rbp) # b
	movl -8(%rbp), %edi # fct param a
	movl -37(%rbp), %esi # fct param b
	movl -12(%rbp), %edx # fct param z
	movl -16(%rbp), %ecx # fct param x
	movl -20(%rbp), %r8d # fct param y
	movl -22(%rbp), %r9d # fct param l
	call h
	movl %eax, -41(%rbp)
	movl -41(%rbp), %eax
	movb %al , -37(%rbp) # b
	movl -37(%rbp), %eax
	addq $41, %rsp
=======
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
>>>>>>> develop
	popq %rbp
	ret

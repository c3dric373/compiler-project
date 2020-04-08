f:
	pushq %rbp
	movq %rsp, %rbp
	subq $9, %rsp
	movl %edi, -4(%rbp)# write argi
	movl %esi, %eax# relocate because arg is a charc
	movb %al, -5(%rbp)# write argc
	movl $2, -9(%rbp)
	movl -9(%rbp), %eax
	addq $9, %rsp
	popq %rbp
	ret
h:
	pushq %rbp
	movq %rsp, %rbp
	subq $9, %rsp
	movl %edi, -4(%rbp)# write argi
	movl %esi, %eax# relocate because arg is a charc
	movb %al, -5(%rbp)# write argc
	movl -5(%rbp), %edi # fct param c
	movl -4(%rbp), %esi # fct param i
	call f
	movl %eax, %eax
	movb %al , -5(%rbp) # c
	movl -5(%rbp) , %eax
	addl -4(%rbp), %eax # c + i
	movl %eax, -9(%rbp)
	movl -9(%rbp), %eax
	addq $9, %rsp
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
	movl -10(%rbp), %edi # fct param b
	movl -8(%rbp), %esi # fct param a
	call h
	movl %eax, %eax
	movb %al , -10(%rbp) # b
	movl -10(%rbp), %eax
	addq $10, %rsp
	popq %rbp
	ret

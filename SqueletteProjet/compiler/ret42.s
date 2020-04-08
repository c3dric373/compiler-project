f:
	pushq %rbp
	movq %rsp, %rbp
	subq $13, %rsp
	movl %edi, -8(%rbp)# write arg i
	movl %esi, %eax# relocate because arg is a char: c
	movb %al, -9(%rbp)# write arg c
	movl $1, -13(%rbp)
	movl -8(%rbp) , %eax
	addl -13(%rbp), %eax # i + !tmp13
	movl %eax, -8(%rbp)
	movl -9(%rbp) , %eax
	addl -8(%rbp), %eax # c + i
	movl %eax, -9(%rbp)
	movl -9(%rbp), %eax
	addq $13, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $14, %rsp
	movl $1, -8(%rbp)
	movl -8(%rbp), %eax
	movl %eax , -4(%rbp) # a
	movb $102, -9(%rbp)
	movl -9(%rbp), %eax
	movb %al , -10(%rbp) # b
	movl -4(%rbp), %edi # fct param a
	movl -10(%rbp), %esi # fct param b
	call f
	movl %eax, -14(%rbp)
	movl -14(%rbp), %eax
	movb %al , -10(%rbp) # b
	movl -10(%rbp), %eax
	addq $14, %rsp
	popq %rbp
	ret

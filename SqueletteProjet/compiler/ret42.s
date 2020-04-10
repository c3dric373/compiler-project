f:
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
	 jmp .f_ret
.f_ret:
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
	 jmp .g_ret
.g_ret:
	addq $16, %rsp
	popq %rbp
	ret
h:
	pushq %rbp
	movq %rsp, %rbp
	subq $33, %rsp
	movl %edi, -8(%rbp)# write arg i
	movl %esi, %eax# relocate because arg is a char: c
	movb %al, -9(%rbp)# write arg c
	movl -8(%rbp), %edi # fct param i
	movl -9(%rbp), %esi # fct param c
	call f
	movl $2, -13(%rbp)
	movl -13(%rbp), %eax
	movl %eax , -17(%rbp) # d
	movl -9(%rbp) , %eax
	addl -8(%rbp), %eax # c + i
	movl %eax, -21(%rbp)
	movl -21(%rbp) , %eax
	addl -17(%rbp), %eax # !tmp21 + d
	movl %eax, -25(%rbp)
	movl $3, -29(%rbp)
	movl -25(%rbp) , %eax
	addl -29(%rbp), %eax # !tmp25 + !tmp29
	movl %eax, -33(%rbp)
	movl -33(%rbp), %eax
	 jmp .h_ret
.h_ret:
	addq $33, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $14, %rsp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movb $102, -9(%rbp)
	movl -9(%rbp), %eax
	movb %al , -10(%rbp) # b
	movl -8(%rbp), %edi # fct param a
	call g
	movl -8(%rbp), %edi # fct param a
	movl -10(%rbp), %esi # fct param b
	call h
	movl %eax, -14(%rbp)
	movl -14(%rbp), %eax
	movb %al , -10(%rbp) # b
	movl -10(%rbp), %eax
	 jmp .main_ret
.main_ret:
	addq $14, %rsp
	popq %rbp
	ret

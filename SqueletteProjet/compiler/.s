factorielle:
	pushq %rbp
	movq %rsp, %rbp
	subq $58, %rsp
	movl %edi, -12(%rbp)# write arg a
	movl %esi, %eax# relocate because arg is a char: b
	movb %al, -13(%rbp)# write arg b
	movl %edx, %eax# relocate because arg is a char: c
	movb %al, -14(%rbp)# write arg c
	movl %ecx, -18(%rbp)# write arg d
	movl %r8d, -22(%rbp)# write arg e
	movl %r9d, -26(%rbp)# write arg pp
	movl $0, -30(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -30(%rbp)
	sete %dl # valeur==!tmp30
	movzbl %dl, %eax
	movl %eax, -34(%rbp)
	cmpl $1, -34(%rbp)
	je .Lfactorielle1
	jmp .Lfactorielle2
.Lfactorielle1: 
	movl $1, -38(%rbp)
	movl -38(%rbp), %eax
	 jmp .Lfactorielle0
.Lfactorielle2: 
	movl $1, -42(%rbp)
	movl -8(%rbp) , %eax
	subl -42(%rbp), %eax# valeur - !tmp42
	movl %eax, -46(%rbp)
	movl -46(%rbp), %eax
	movl %eax , -50(%rbp) # nextval
	movl -50(%rbp), %eax
	movl %eax, -78(%rbp) # fct param nextval
	movl -50(%rbp), %edi # fct param nextval
	movl -13(%rbp), %esi # fct param b
	movl -14(%rbp), %edx # fct param c
	movl -18(%rbp), %ecx # fct param d
	movl -22(%rbp), %r8d # fct param e
	movl -26(%rbp), %r9d # fct param pp
	call factorielle
	movl %eax, -54(%rbp)
	movl -8(%rbp) , %eax
	imull -54(%rbp), %eax # valeur * !tmp54
	movl %eax, -58(%rbp)
	movl -58(%rbp), %eax
.Lfactorielle0: 
	addq $58, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $18, %rsp
	movl $7, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movb $101, -13(%rbp)
	movl -13(%rbp), %eax
	movb %al , -14(%rbp) # e
	movl -8(%rbp), %eax
	movl %eax, -42(%rbp) # fct param a
	movl -8(%rbp), %edi # fct param a
	movl -14(%rbp), %esi # fct param e
	movl -14(%rbp), %edx # fct param e
	movl -8(%rbp), %ecx # fct param a
	movl -8(%rbp), %r8d # fct param a
	movl -8(%rbp), %r9d # fct param a
	call factorielle
	movl %eax, -18(%rbp)
	movl -18(%rbp), %eax
	movl %eax , -12(%rbp) # b
	movl -12(%rbp), %eax
	addq $18, %rsp
	popq %rbp
	ret

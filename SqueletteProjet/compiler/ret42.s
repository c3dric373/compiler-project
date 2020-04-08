factorielle:
	pushq %rbp
	movq %rsp, %rbp
	subq $40, %rsp
	movl %edi, -8(%rbp)# write arg valeur
	movl $0, -12(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -12(%rbp)
	sete %dl # valeur==!tmp12
	movzbl %dl, %eax
	movl %eax, -16(%rbp)
	cmpl $1, -16(%rbp)
	je .Lfactorielle1
	jmp .Lfactorielle2
.Lfactorielle1: 
	movl $1, -20(%rbp)
	movl -20(%rbp), %eax
	 jmp .Lfactorielle0
.Lfactorielle2: 
	movl $1, -24(%rbp)
	movl -8(%rbp) , %eax
	subl -24(%rbp), %eax# valeur - !tmp24
	movl %eax, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -32(%rbp) # b
	movl -32(%rbp), %edi # fct param b
	call factorielle
	movl %eax, -36(%rbp)
	movl -8(%rbp) , %eax
	imull -36(%rbp), %eax # valeur * !tmp36
	movl %eax, -40(%rbp)
	movl -40(%rbp), %eax
.Lfactorielle0: 
	addq $40, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movl $7, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl -8(%rbp), %edi # fct param a
	call factorielle
	movl %eax, -16(%rbp)
	movl -16(%rbp), %eax
	movl %eax , -12(%rbp) # b
	movl -12(%rbp), %eax
	addq $16, %rsp
	popq %rbp
	ret

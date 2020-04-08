factorielle:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movl %edi, -4(%rbp)# write arg valeur
	movl $0, -8(%rbp)
	movl -4(%rbp), %eax
	cmpl  %eax, -8(%rbp)
	sete %dl # valeur==!tmp8
	movzbl %dl, %eax
	movl %eax, -12(%rbp)
	cmpl $1, -12(%rbp)
	je .Lfactorielle1
	jmp .Lfactorielle2
.Lfactorielle1: 
	movl $1, -16(%rbp)
	movl -16(%rbp), %eax
	 jmp .Lfactorielle0
.Lfactorielle2: 
.Lfactorielle0: 
	addq $16, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $12, %rsp
	movl $7, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl -8(%rbp), %edi # fct param a
	call factorielle
	movl %eax, %eax
	movl %eax , -12(%rbp) # b
	movl -12(%rbp), %eax
	addq $12, %rsp
	popq %rbp
	ret

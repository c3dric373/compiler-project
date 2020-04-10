<<<<<<< HEAD
pair:
	pushq %rbp
	movq %rsp, %rbp
	subq $52, %rsp
	movl %edi, -8(%rbp)# write arg valeur
	movl $2, -16(%rbp)
	movl -8(%rbp) , %eax
	subl -16(%rbp), %eax# valeur - !tmp16
	movl %eax, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp) # x
	movl $0, -28(%rbp)
	movl -24(%rbp), %eax
	cmpl  %eax, -28(%rbp)
	sete %dl # x==!tmp28
	movzbl %dl, %eax
	movl %eax, -32(%rbp)
	cmpl $1, -32(%rbp)
	je .Lpair1
	jmp .Lpair2
.Lpair1: 
	movl $1, -36(%rbp)
	movl -36(%rbp), %eax
	 jmp .Lpair0
.Lpair2: 
	movl $1, -40(%rbp)
	movl -24(%rbp), %eax
	cmpl  %eax, -40(%rbp)
	sete %dl # x==!tmp40
	movzbl %dl, %eax
	movl %eax, -44(%rbp)
	cmpl $1, -44(%rbp)
	je .Lpair4
	jmp .Lpair5
.Lpair4: 
	movl $0, -48(%rbp)
	movl -48(%rbp), %eax
	 jmp .Lpair3
.Lpair5: 
	movl -24(%rbp), %edi # fct param x
	call pair
	movl %eax, -52(%rbp)
	movl -52(%rbp), %eax
	movl %eax , -12(%rbp) # resultat
	movl -12(%rbp), %eax
.Lpair3: 
.Lpair0: 
	addq $52, %rsp
=======
f:
	pushq %rbp
	movq %rsp, %rbp
	subq $33, %rsp
	movl %edi, -12(%rbp)# write arg i
	movl %esi, %eax# relocate because arg is a char: c
	movb %al, -13(%rbp)# write arg c
	movl %edx, -17(%rbp)# write arg b
	movl %ecx, -21(%rbp)# write arg e
	movl %r8d, -25(%rbp)# write arg f
	movl %r9d, -29(%rbp)# write arg h
	movl -8(%rbp), %eax
	movl %eax , -33(%rbp) # carre
	movl -33(%rbp), %eax
	addq $33, %rsp
>>>>>>> develop
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
<<<<<<< HEAD
	subq $16, %rsp
	movl $8, -4(%rbp)
=======
	subq $14, %rsp
	movl $1, -4(%rbp)
>>>>>>> develop
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movb $102, -9(%rbp)
	movl -9(%rbp), %eax
	movb %al , -10(%rbp) # b
	movl -8(%rbp), %eax
	movl %eax, -38(%rbp) # fct param a
	movl -8(%rbp), %edi # fct param a
<<<<<<< HEAD
	call pair
	movl %eax, -16(%rbp)
	movl -16(%rbp), %eax
	movl %eax , -12(%rbp) # b
	movl -12(%rbp), %eax
	addq $16, %rsp
=======
	movl -10(%rbp), %esi # fct param b
	movl -8(%rbp), %edx # fct param a
	movl -8(%rbp), %ecx # fct param a
	movl -8(%rbp), %r8d # fct param a
	movl -8(%rbp), %r9d # fct param a
	call f
	movl %eax, -14(%rbp)
	movl -14(%rbp), %eax
	movb %al , -10(%rbp) # b
	movl -10(%rbp), %eax
	addq $14, %rsp
>>>>>>> develop
	popq %rbp
	ret

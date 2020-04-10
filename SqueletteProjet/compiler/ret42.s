pair:
	pushq %rbp
	movq %rsp, %rbp
	subq $40, %rsp
	movl %edi, -8(%rbp)# write arg valeur
	movl $0, -16(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -16(%rbp)
	sete %dl # valeur==!tmp16
	movzbl %dl, %eax
	movl %eax, -20(%rbp)
	cmpl $1, -20(%rbp)
	je .Lpair1
	jmp .Lpair2
.Lpair1: 
	movl $1, -24(%rbp)
	movl -24(%rbp), %eax
	 jmp .pair_ret
	 jmp .Lpair0
.Lpair2: 
	movl $1, -28(%rbp)
	movl -8(%rbp) , %eax
	subl -28(%rbp), %eax# valeur - !tmp28
	movl %eax, -32(%rbp)
	movl -32(%rbp), %eax
	movl %eax , -36(%rbp) # x
	movl -36(%rbp), %edi # fct param x
	call impair
	movl %eax, -40(%rbp)
	movl -40(%rbp), %eax
	movl %eax , -12(%rbp) # resultat
	movl -12(%rbp), %eax
	 jmp .pair_ret
.Lpair0: 
.pair_ret:
	addq $40, %rsp
	popq %rbp
	ret
impair:
	pushq %rbp
	movq %rsp, %rbp
	subq $52, %rsp
	movl %edi, -8(%rbp)# write arg valeur
	movl $1, -16(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -16(%rbp)
	sete %dl # valeur==!tmp16
	movzbl %dl, %eax
	movl %eax, -20(%rbp)
	cmpl $1, -20(%rbp)
	je .Limpair1
	jmp .Limpair2
.Limpair1: 
	movl $1, -24(%rbp)
	movl -24(%rbp), %eax
	 jmp .impair_ret
	 jmp .Limpair0
.Limpair2: 
	movl $0, -28(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -28(%rbp)
	sete %dl # valeur==!tmp28
	movzbl %dl, %eax
	movl %eax, -32(%rbp)
	cmpl $1, -32(%rbp)
	je .Limpair3
	jmp .Limpair4
.Limpair3: 
	movl $0, -36(%rbp)
	movl -36(%rbp), %eax
	 jmp .impair_ret
.Limpair4: 
	movl $1, -40(%rbp)
	movl -8(%rbp) , %eax
	subl -40(%rbp), %eax# valeur - !tmp40
	movl %eax, -44(%rbp)
	movl -44(%rbp), %eax
	movl %eax , -48(%rbp) # x
	movl -48(%rbp), %edi # fct param x
	call pair
	movl %eax, -52(%rbp)
	movl -52(%rbp), %eax
	movl %eax , -12(%rbp) # resultat
	movl -12(%rbp), %eax
	 jmp .impair_ret
.Limpair0: 
.impair_ret:
	addq $52, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movl $22, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl -8(%rbp), %edi # fct param a
	call pair
	movl %eax, -16(%rbp)
	movl -16(%rbp), %eax
	movl %eax , -12(%rbp) # b
	movl -12(%rbp), %eax
	 jmp .main_ret
.main_ret:
	addq $16, %rsp
	popq %rbp
	ret

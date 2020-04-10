.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $80, %rsp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $0, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp) # b
	movl $2, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp) # d
	movl $30, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -32(%rbp) # c
.Lmain0: 
	movl $1, -36(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -36(%rbp)
	sete %dl # a==!tmp36
	movzbl %dl, %eax
	movl %eax, -40(%rbp)
	cmpl $1, -40(%rbp)
	je .Lmain1
	jmp .Lmain2
.Lmain1: 
	movl $0, -44(%rbp)
	movl -16(%rbp), %eax
	cmpl  %eax, -44(%rbp)
	sete %dl # b==!tmp44
	movzbl %dl, %eax
	movl %eax, -48(%rbp)
	cmpl $1, -48(%rbp)
	je .Lmain3
	jmp .Lmain4
.Lmain3: 
	movl $2, -52(%rbp)
	movl -52(%rbp), %eax
	movl %eax , -8(%rbp) # a
.Lmain4: 
.Lmain5: 
	movl $3, -56(%rbp)
	movl -56(%rbp), %eax
	cmp  %eax, -16(%rbp)
	setb %dl # b<!tmp56
	movzbl %dl, %eax
	movl %eax, -60(%rbp)
	cmpl $1, -60(%rbp)
	je .Lmain6
	jmp .Lmain7
.Lmain6: 
	movl $1, -64(%rbp)
	movl -64(%rbp), %eax
	movl %eax , -68(%rbp) # c
	movl -16(%rbp) , %eax
	addl -68(%rbp), %eax # b + c
	movl %eax, -72(%rbp)
	movl -72(%rbp), %eax
	movl %eax , -16(%rbp) # b
	 jmp .Lmain5
.Lmain7: 
	movl -16(%rbp) , %eax
	addl -24(%rbp), %eax # b + d
	movl %eax, -76(%rbp)
	movl -76(%rbp), %eax
	movl %eax , -24(%rbp) # d
	 jmp .Lmain0
.Lmain2: 
	movl -32(%rbp) , %eax
	subl -24(%rbp), %eax# c - d
	movl %eax, -80(%rbp)
	movl -80(%rbp), %eax
	 jmp .main_ret
.main_ret:
	addq $80, %rsp
	popq %rbp
	ret

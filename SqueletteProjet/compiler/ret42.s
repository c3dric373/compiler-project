.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $5, -20(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -20(%rbp)
	sete %dl # a==!tmp20
	movzbl %dl, %eax
	movl %eax, -24(%rbp)
	cmpl $1, -24(%rbp)
	je .Lmain1
	jmp .Lmain2
.Lmain1: 
	movl -8(%rbp), %eax
	addq $32, %rsp
	popq %rbp
	ret
	 jmp .Lmain0
.Lmain2: 
	movl $4, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -12(%rbp) # b
	movl $2, -32(%rbp)
	movl -32(%rbp), %eax
	movl %eax , -16(%rbp) # c
	movl -12(%rbp), %eax
	addq $32, %rsp
	popq %rbp
	ret
.Lmain0: 
	movl -16(%rbp), %eax
	addq $32, %rsp
	popq %rbp
	ret
	addq $32, %rsp
	popq %rbp
	ret

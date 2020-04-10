.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $36, %rsp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl $5, -20(%rbp)
	movl -8(%rbp), %eax
	cmpl  %eax, -20(%rbp)
	sete %dl # a==!tmp20
	movzbl %dl, %eax
	movl %eax, -24(%rbp)
	cmpl $0, -24(%rbp)
	je .Lmain2
	jmp .Lmain1
.Lmain1: 
	movl $3, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -32(%rbp) # d
	 jmp .Lmain0
.Lmain2: 
	movl $4, -36(%rbp)
	movl -36(%rbp), %eax
	movl %eax , -12(%rbp) # b
.Lmain0: 
	movl 12000(%rbp), %eax
	 jmp .main_ret
.main_ret:
	addq $36, %rsp
	popq %rbp
	ret

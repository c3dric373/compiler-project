.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $3, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $2, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -16(%rbp)
.L0: 
	movl $3, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -24(%rbp)
.L1: 
	movl $3, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -32(%rbp)
	movl $3, -1(%rbp)
	movl -32(%rbp) , %eax
	addl -1(%rbp), %eax
	movl %eax, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -24(%rbp)
	movl $3, -1(%rbp)
	movl -1(%rbp) , %eax
	addl -24(%rbp), %eax
	movl %eax, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -16(%rbp)
	movl -16(%rbp), %eax
	popq %rbp
	ret

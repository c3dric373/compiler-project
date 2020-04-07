f:
	pushq %rbp
	movq %rsp, %rbp
	subq $17, %rsp
	movl 16(%rbp), %eax# get arg i
	movl %eax , -4(%rbp)  # write argi
	movl 20(%rbp), %eax# get arg c
	movl %eax , -5(%rbp)  # write argc
	movl $1, -9(%rbp)
	movl -4(%rbp) , %eax
	addl -9(%rbp), %eax # i + !tmp9
	movl %eax, -13(%rbp)
	movl -13(%rbp), %eax
	movl %eax , -4(%rbp) # i
	movl -5(%rbp) , %eax
	addl -4(%rbp), %eax # c + i
	movl %eax, -17(%rbp)
	movl -17(%rbp), %eax
	movb %al , -5(%rbp) # c
	movl -5(%rbp), %eax
	addq $17, %rsp
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $10, %rsp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movb $102, -9(%rbp)
	movl -9(%rbp), %eax
	movb %al , -10(%rbp) # b
	movl -10(%rbp), %eax
	movb %al , -14(%rbp) # fct param -14(%rbp)
	movl -8(%rbp), %eax
	movl %eax , -18(%rbp) # fct param -18(%rbp)
	call f
	movl %eax, %eax
	movb %al , -10(%rbp) # b
	movl -10(%rbp), %eax
	addq $10, %rsp
	popq %rbp
	ret

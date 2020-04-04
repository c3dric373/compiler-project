.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -1(%rbp)
	movl -1(%rbp), %eax
	NEG %eax
	movl %eax, -1(%rbp)
	movl -1(%rbp), %eax
	movl %eax , -12(%rbp)
	movl -12(%rbp), %eax
	popq %rbp
	ret

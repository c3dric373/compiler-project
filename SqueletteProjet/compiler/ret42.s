.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, %eax
	movl %eax, -4(%rbp)
	movl $3, %eax
	movl %eax, -8(%rbp)
	movl -4 (%rbp) , %eax
	movl %eax, %ebx
	movl -8 (%rbp) , %eax
	addl %ebx, %eax
	movl %eax, -12(%rbp)
	movl -12 (%rbp) , %eax
	popq %rbp
	ret

.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl -4 (%rbp) , %eax
	movl %eax, -12 (%rbp)
	movl -8 (%rbp) , %eax
	addl -12 (%rbp) , %eax
	popq %rbp
	ret

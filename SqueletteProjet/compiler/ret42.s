.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $6, %eax
	movl  %eax,  -4(%rbp)
	movl -4(%rbp), %eax
	popq %rbp
	ret

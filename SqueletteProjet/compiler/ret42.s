.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, %eax
	movl %eax, %ecx
	movl $3, %eax
	imull %ecx, %eax
	NEG %eax
	movl %eax, -4(%rbp)
	movl $3, %eax
	NEG %eax
	popq %rbp
	ret

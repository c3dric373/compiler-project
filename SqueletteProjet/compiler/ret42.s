.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $8, %eax
	movl %eax, %ebx
	movl $5, %eax
	imull %ebx, %eax
	movl %eax, %ebx
	movl $4, %eax
	movl %eax, %ebx
	movl $7, %eax
	imull %ebx, %eax
	addl %ebx, %eax
	movl %eax, -4(%rbp)
	movl -4 (%rbp) , %eax
	popq %rbp
	ret

.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $10, -20(%rbp)
	movl -20(%rbp), %eax
	cmpl -8(%rbp), %eax
	jg.L0
	jmp .L1
.L0: 
	movl $2, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -16(%rbp)
.L1: 
	movl -16(%rbp), %eax
	popq %rbp
	ret

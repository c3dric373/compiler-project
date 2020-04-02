.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $9, -16(%rbp)
	movl -16(%rbp), %eax
	cmp  %eax, -8(%rbp)
	setbe %dl
	mov %dl, -20(%rbp)
	cmp $1, -20(%rbp)
	jne .L0
	jmp .L1
.L0: 
	movl $2, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -12(%rbp)
.L1: 
	movl -12(%rbp), %eax
	popq %rbp
	ret

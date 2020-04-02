.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $1, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp)
	movl $1, -20(%rbp)
	movl -8(%rbp), %eax
	cmp  %eax, -20(%rbp)
	sete %dl
	mov %dl, -24(%rbp)
	movl -24(%rbp), %eax
	cmp  %eax, 0
    jmp .L1
	jz .L0
	jmp .L1
.L0: 
	movl $2, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -16(%rbp)
.L1: 
	popq %rbp
	ret

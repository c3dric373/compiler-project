.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $1, -16(%rbp)
	movl -8(%rbp), %eax
	cmp  %eax, -16(%rbp)
	sete %dl
	mov %dl, -20(%rbp)
	movl -20(%rbp), %eax
	movl  $1, %ebx
	cmp %eax, %ebx
	je .L0
	jmp .L1
.L0: 
	movl $2, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -12(%rbp)
.L1: 
	movl -20(%rbp), %eax
	popq %rbp
	ret

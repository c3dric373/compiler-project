	.file	"ret42.c"
	.text
	.globl	main
	.type	main, @function
main:
<<<<<<< HEAD
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$23, -12(%rbp)
	movl	$2, -8(%rbp)
	movl	-8(%rbp), %eax
	addl	$2, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
=======
	pushq %rbp
	movq %rsp, %rbp
	movl $1, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
.L0: 
	movl $5, -12(%rbp)
	movl -12(%rbp), %eax
	cmp  %eax, -8(%rbp)
	setb %dl
	movzbl %dl, %eax
	movl %eax, -16(%rbp)
	cmpl $1, -16(%rbp)
	je .L1
	jmp .L2
.L1: 
	movl $1, -20(%rbp)
	movl -8(%rbp) , %eax
	addl -20(%rbp), %eax
	movl %eax, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -8(%rbp)
	 jmp .L0
.L2: 
	movl -8(%rbp), %eax
	popq %rbp
>>>>>>> develop
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Arch Linux 9.3.0-1) 9.3.0"
	.section	.note.GNU-stack,"",@progbits

	.file	"ret43.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$1, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L2
	movl	$2, -8(%rbp)
.L2:
	movl	-8(%rbp), %eax
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Arch Linux 9.3.0-1) 9.3.0"
	.section	.note.GNU-stack,"",@progbits

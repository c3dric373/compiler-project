	.file	"ret42.c"
	.text
	.globl	main
	.type	main, @function
main:
<<<<<<< HEAD
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movb	$97, -7(%rbp)
	movb	$98, -6(%rbp)
	movzbl	-7(%rbp), %eax
	movzbl	-6(%rbp), %edx
	imull	%edx, %eax
	movb	%al, -5(%rbp)
	movsbl	-5(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
=======
	pushq %rbp
	movq %rsp, %rbp
	movl $6, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
.L0: 
	movl $5, -12(%rbp)
	movl -12(%rbp), %eax
	cmp  %eax, -8(%rbp)
	seta %dl
	movzbl %dl, %eax
	movl %eax, -16(%rbp)
	cmpl $1, -16(%rbp)
	je .L1
	jmp .L2
.L1: 
	movl $1, -20(%rbp)
	movl -8(%rbp) , %eax
	subl -20(%rbp), %eax
	movl %eax, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax , -8(%rbp)
	 jmp .L0
.L2: 
	movl $3, -28(%rbp)
	movl -28(%rbp), %eax
	movl %eax , -32(%rbp)
	movl $3, -36(%rbp)
	movl -36(%rbp), %eax
	cmp  %eax, -32(%rbp)
	seta %dl
	movzbl %dl, %eax
	movl %eax, -40(%rbp)
	cmpl $1, -40(%rbp)
	je .L3
	jmp .L4
.L3: 
	movl $6, -44(%rbp)
	movl -44(%rbp), %eax
	movl %eax , -32(%rbp)
.L4: 
	movl -32(%rbp), %eax
	popq %rbp
>>>>>>> develop
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Arch Linux 9.3.0-1) 9.3.0"
	.section	.note.GNU-stack,"",@progbits

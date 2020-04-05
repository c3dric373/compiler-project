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
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)
	movl $2, -20(%rbp)
	movl -20(%rbp), %eax
	cmp  %eax, -8(%rbp)
	seta %dl
	movzbl %dl, %eax
	movl %eax, -24(%rbp)
	cmpl $1, -24(%rbp)
	je .L0
	jmp .L1
.L0: 
	movl $1, -28(%rbp)
	movl -8(%rbp) , %eax
	subl -28(%rbp), %eax
	movl %eax, -32(%rbp)
	movl -32(%rbp), %eax
	movl %eax , -16(%rbp)
	movl $1, -36(%rbp)
	movl -36(%rbp), %eax
	cmp  %eax, -16(%rbp)
	seta %dl
	movzbl %dl, %eax
	movl %eax, -40(%rbp)
	cmpl $1, -40(%rbp)
	je .L3
	jmp .L4
.L3: 
	movl $3, -44(%rbp)
	movl -44(%rbp), %eax
	movl %eax , -12(%rbp)
	 jmp .L2
.L4: 
	movl $5, -48(%rbp)
	movl -48(%rbp), %eax
	movl %eax , -12(%rbp)
	movl $2, -52(%rbp)
	movl -16(%rbp), %eax
	cmpl  %eax, -52(%rbp)
	sete %dl
	movzbl %dl, %eax
	movl %eax, -56(%rbp)
	cmpl $1, -56(%rbp)
	je .L5
	jmp .L6
.L5: 
	movl $3, -60(%rbp)
	movl -60(%rbp), %eax
	movl %eax , -8(%rbp)
.L6: 
.L2: 
	movl $0, -64(%rbp)
	movl -64(%rbp), %eax
	cmp  %eax, -8(%rbp)
	seta %dl
	movzbl %dl, %eax
	movl %eax, -68(%rbp)
	cmpl $1, -68(%rbp)
	je .L8
	jmp .L9
.L8: 
	movl $7, -72(%rbp)
	movl -72(%rbp), %eax
	movl %eax , -76(%rbp)
	movl -76(%rbp), %eax
	movl %eax , -8(%rbp)
	 jmp .L7
.L9: 
	movl $10, -80(%rbp)
	movl -80(%rbp), %eax
	movl %eax , -12(%rbp)
.L7: 
	movl $5, -84(%rbp)
	movl -84(%rbp), %eax
	movl %eax , -88(%rbp)
.L1: 
	movl -16(%rbp), %eax
	popq %rbp
>>>>>>> develop
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Arch Linux 9.3.0-1) 9.3.0"
	.section	.note.GNU-stack,"",@progbits

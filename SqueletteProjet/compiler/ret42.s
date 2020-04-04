.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $3, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp)# name:a
	movl $2, -12(%rbp)
	movl -12(%rbp), %eax
	movl %eax , -16(%rbp)# name:c
.L0: 
	movl $3, -20(%rbp)
	movl -20(%rbp), %eax
	movl %eax , -24(%rbp)# name:d
.L1: 
	movl $4, -28(%rbp)
	movl -24(%rbp), %eax
	cmpl  %eax, -28(%rbp)# d==!tmp28
	sete %dl
	movzbl %dl, %eax
	movl %eax, -32(%rbp)
	cmpl $1, -32(%rbp)
	je .L3
	jmp .L4
.L3: 
	movl $5, -36(%rbp)
	movl -36(%rbp), %eax
	movl %eax , -40(%rbp)# name:f
	movl $1, -44(%rbp)
	movl -40(%rbp) , %eax# move: f
	subl -44(%rbp), %eax# f - !tmp44
	movl %eax, -48(%rbp)
	movl -48(%rbp), %eax
	movl %eax , -16(%rbp)# name:c
	 jmp .L2
.L4: 
	movl $6, -52(%rbp)
	movl -52(%rbp), %eax
	movl %eax , -56(%rbp)# name:f
.L5: 
	movl $1, -60(%rbp)
	movl -60(%rbp), %eax
	cmp  %eax, -56(%rbp)
	seta %dl
	movzbl %dl, %eax
	movl %eax, -64(%rbp)
	cmpl $1, -64(%rbp)
	je .L6
	jmp .L7
.L6: 
	movl $2, -68(%rbp)
	movl $1, -72(%rbp)
	movl -68(%rbp) , %eax# move: !tmp68
	subl -72(%rbp), %eax# !tmp68 - !tmp72
	movl %eax, -76(%rbp)
	movl -76(%rbp), %eax
	movl %eax , -80(%rbp)# name:z
	movl -16(%rbp) , %eax
	addl -80(%rbp), %eax
	movl %eax, -84(%rbp)
	movl -84(%rbp) , %eax
	addl -24(%rbp), %eax
	movl %eax, -88(%rbp)
	movl -88(%rbp), %eax
	movl %eax , -16(%rbp)# name:c
	movl $1, -92(%rbp)
	movl -56(%rbp) , %eax# move: f
	subl -92(%rbp), %eax# f - !tmp92
	movl %eax, -96(%rbp)
	movl -96(%rbp), %eax
	movl %eax , -56(%rbp)# name:f
	movl $1, -100(%rbp)
	movl -100(%rbp), %eax
	movl %eax , -24(%rbp)# name:d
	 jmp .L5
.L7: 
.L2: 
	movl -16(%rbp), %eax
	popq %rbp
	ret

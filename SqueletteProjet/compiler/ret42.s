.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $1, %eax
	movl %eax, -16 (%rbp)
	movl $55, %eax
	addl -16 (%rbp) , %eax
	movl %eax, -20 (%rbp)
	movl $3, %eax
	addl -20 (%rbp) , %eax
	movl %eax, -24 (%rbp)
	movl $10, %eax
	movl %eax, -28 (%rbp)
	movl $5, %eax
	movl %eax, -32 (%rbp)
	movl -28 (%rbp), %eax
	subl -32 (%rbp), %eax
	movl %eax, -36 (%rbp)
	movl $32, %eax
	movl %eax, -40 (%rbp)
	movl -36 (%rbp), %eax
	subl -40 (%rbp), %eax
	movl %eax, -44 (%rbp)
	movl $31, %eax
	movl %eax, -48 (%rbp)
	movl -44 (%rbp), %eax
	subl -48 (%rbp), %eax
	addl -24 (%rbp) , %eax
	movl %eax, -4(%rbp)
	movl $2, %eax
	movl %eax, -52 (%rbp)
	movl -4 (%rbp) , %eax
	addl -52 (%rbp) , %eax
	movl %eax, -8(%rbp)
	movl $3, %eax
	movl %eax, -56 (%rbp)
	movl -4 (%rbp) , %eax
	movl %eax, -60 (%rbp)
	movl -8 (%rbp) , %eax
	imull -60 (%rbp) , %eax
	movl %eax, -64 (%rbp)
	movl $5, %eax
	imull -64 (%rbp) , %eax
	addl -56 (%rbp) , %eax
	movl %eax, -68 (%rbp)
	movl -12 (%rbp) , %eax
	addl -68 (%rbp) , %eax
	movl %eax, -12(%rbp)
	movl -12 (%rbp) , %eax
	popq %rbp
	ret

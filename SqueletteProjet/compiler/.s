.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	movl $5, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl 12000(%rbp), %eax
	 jmp .main_ret
.main_ret:
	addq $8, %rsp
	popq %rbp
	ret

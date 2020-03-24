.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
	movl $8, %eax
	movl %eax, %edx
	movl $2, %eax
	movl %eax, %ebx
	movl $3, %eax
	addl %ebx, %eax
	movl %eax, %esi
	movl %edx, %eax
	subl %esi, %eax
	movl %eax, %edx
	movl $1, %eax
	movl %eax, %esi
	movl %edx, %eax
	subl %esi, %eax
	movl %eax, -4(%rbp)
	movl -4 (%rbp) , %eax
	popq %rbp
	ret

.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
<<<<<<< HEAD
test: 
	movl $3, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # d
	popq %rbp
	ret
.globl	main
main:
	pushq %rbp
	movq %rsp, %rbp
main: 
	movl $4, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -8(%rbp) # a
	movl -8(%rbp), %eax
=======
	movl $2, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax , -1(%rbp) # a
	movl -1(%rbp), %eax
>>>>>>> develop
	popq %rbp
	ret

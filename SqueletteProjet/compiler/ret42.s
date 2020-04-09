.globl	main
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        call    getchar
        movb    %al, -1(%rbp)
        movsbl  -1(%rbp), %eax
        movl    %eax, %edi
        call    putchar
        movl    $0, %eax
        leave
        ret

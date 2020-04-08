f:
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -4(%rbp)
        movl    %esi, %eax
        movb    %al, -8(%rbp)
        movl    $2, %eax
        popq    %rbp
        ret
h:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $8, %rsp
        movl    %edi, -4(%rbp)
        movl    %esi, %eax
        movb    %al, -8(%rbp)
        movl  -8(%rbp), %edx
        movl    -4(%rbp), %eax
        movl    %edx, %esi
        movl    %eax, %edi
        call    f
        movb    %al, -8(%rbp)
        movl    -4(%rbp), %eax
        movl    %eax, %edx
        movl  -8(%rbp), %eax
        addl    %edx, %eax
        leave
        ret
.globl main
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movl    $1, -4(%rbp)
        movb    $102, -5(%rbp)
        movl  -5(%rbp), %edx
        movl    -4(%rbp), %eax
        movl    %edx, %esi
        movl    %eax, %edi
        call    h
        movb    %al, -5(%rbp)
        movsbl  -5(%rbp), %eax
        leave
        ret

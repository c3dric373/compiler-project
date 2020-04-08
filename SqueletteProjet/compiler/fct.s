test:
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -4(%rbp)
        movl    $5, -4(%rbp)
        nop
        popq    %rbp
        ret
.globl main
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movl    $5, -4(%rbp)
        movl    -4(%rbp), %eax
        movl    %eax, %edi
        call    test
        movl    -4(%rbp), %eax
        leave
        ret

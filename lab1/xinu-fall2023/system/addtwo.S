/* Simple code to add two integers passed to addtwo() coded
	in AT&T assembly. Assumes caller follows CDECL. */

        .text
        .globl addtwo

addtwo:
        pushl   %ebp
        movl    %esp,%ebp
        pushl   %ebx
        movl    8(%ebp),%eax
        movl    12(%ebp),%ebx
        addl    %ebx,%eax
        popl    %ebx
        movl    (%esp),%ebp
        add     $4,%esp
        ret

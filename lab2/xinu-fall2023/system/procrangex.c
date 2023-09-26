/* procrangex.c - procrangex */

#include <xinu.h>

extern char *pruserstack;
extern char *prkstack;

/*------------------------------------------------------------------------
 *  procrangex  -  Output number of processes that satisifies
 *------------------------------------------------------------------------
 */
syscall procrangex(uint16 proc_type, pid32 pid_min, pid32 pid_max) {

    int numproc;

    /* Setting procrangex's syscall number to 6 */
    int syscall = 8; 

    struct  procent *prptr = &proctab[getpid()];; /* Pointer to proc. table entry */
    // //pruserstack = prptr->prstkbase; /* Get the top of user stack */
    prkstack = prptr->prsyscallkstack; /* Get the top of kernel stack */


    /* Move system call number into EBX */
    /* Move first argument into ECX */
    /* Move second argument into EDX */

    asm("movl %1, %%ebx\n\t"
        "movl %2, %%ecx\n\t"
        "movl %3, %%edx\n\t"
        "pushl %4\n\t"
        "int $34 \n\t"
        "movl %%eax, %0\n\t"
        : "=r" (numproc)
        : "g" (syscall), "g" (proc_type), "g" (pid_min), "g" (pid_max)
        : "%ebx", "%ecx", "%edx", "%esi", "%edi");
    /* : Output Operand */
    /* : Input Operand - syscall number and pid*/
    /* : Adding EBX and ECX into clobber list */
        /* Using the clobber list obviates the need to save/restore register values used by the system call dispatcher. */
    return numproc;
}
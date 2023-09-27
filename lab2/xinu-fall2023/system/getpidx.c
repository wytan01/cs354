/* getpidx.c - getpidx */

#include <xinu.h>

extern char *prustack;
extern char *prkstack;

/*------------------------------------------------------------------------
 *  getpidx  -  Output current process' pid
 *------------------------------------------------------------------------
 */
syscall getpidx() {

    int pid;

    /* Setting getpidx's syscall number to 5 */
    int syscall = 5; 

    struct  procent *prptr = &proctab[getpid()]; /* Pointer to proc. table entry */
    prkstack = prptr->prsyscallkstack; /* Get the top of kernel stack */

    /* Move system call number into EBX */
    asm("movl %1, %%ebx\n\t"
        "int $33 \n\t"
        "movl %%eax, %0\n\t"
        : "=r" (pid)
        : "r" (syscall)
        : "%ebx", "%esi", "%edi");
    /* : Output Operand */
    /* : Input Operand - syscall number and pid*/
    /* : Adding EBX and ECX into clobber list */
        /* Using the clobber list obviates the need to save/restore register values used by the system call dispatcher. */
    
    prptr->pruserstack = prustack; /* Transferred to global var by ESP */
    
    return pid;
}
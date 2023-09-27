/* getpriox.c - getpriox */

#include <xinu.h>

extern char *prustack;
extern char *prkstack;

/*------------------------------------------------------------------------
 *  getpriox  -  Output priority of process
 *------------------------------------------------------------------------
 */
syscall getpriox(pid32 pid) {

    int prio;

    /* Setting listancestorsx's syscall number to 6 */
    int syscall = 9; 

    struct  procent *prptr = &proctab[getpid()];; /* Pointer to proc. table entry */
    prkstack = prptr->prsyscallkstack; /* Get the top of kernel stack */

    /* Move system call number into EBX */
    /* Move first argument into ECX*/

    asm("movl %1, %%ebx\n\t"
        "movl %2, %%ecx\n\t"
        "int $33 \n\t"
        "movl %%eax, %0\n\t"
        : "=r" (prio)
        : "r" (syscall), "r" (pid)
        : "%ebx", "%ecx", "%esi", "%edi");
    /* : Output Operand */
    /* : Input Operand - syscall number and pid*/
    /* : Adding EBX and ECX into clobber list */
        /* Using the clobber list obviates the need to save/restore register values used by the system call dispatcher. */
    
    prptr->pruserstack = prustack; /* Transferred to global var by ESP */
    
    return prio;
}
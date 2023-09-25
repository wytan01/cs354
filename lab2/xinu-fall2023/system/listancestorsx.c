/* listancestorsx.c - listancestorsx */

#include <xinu.h>

extern char *pruserstack;
extern char *prsyscallkstack;

/*------------------------------------------------------------------------
 *  listancestorsx  -  Output all ancestor processes and returned their number
 *------------------------------------------------------------------------
 */
syscall listancestorsx(pid32 pid) {
    int numancestors;

    /* Setting listancestorsx's syscall number to 6 */
    int syscall = 6; 

    struct  procent *prptr = &proctab[pid];; /* Pointer to proc. table entry */
    pruserstack = prptr->prstkbase; /* Get the top of user stack */
    prsyscallkstack = prptr->prkstack; /* Get the top of user stack */


    /* Move system call number into EBX */
    /* Move first argument into ECX*/

    asm("movl %1, %%ebx\n\t"
        "movl %2, %%ecx\n\t"
        "int $33 \n\t"
        "movl %%eax, %0\n\t"
        : "=r" (numancestors)
        : "r" (syscall), "r" (pid)
        : "%ebx", "%ecx", "%esi", "%edi");
    /* : Output Operand */
    /* : Input Operand - syscall number and pid*/
    /* : Adding EBX and ECX into clobber list */
        /* Using the clobber list obviates the need to save/restore register values used by the system call dispatcher. */
    kprintf("in listancestorsx\n");
    return numancestors;
}
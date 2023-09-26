/* chpriox.c - chpriox */

#include <xinu.h>

extern char *pruserstack;
extern char *prkstack;

/*------------------------------------------------------------------------
 *  chpriox  -  Change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
syscall chpriox(
	  pid32		pid,		/* ID of process to change	*/
	  pri16		newprio		/* New priority			*/
	)
{

    int oldprio;

    /* Setting chpriox's syscall number to 7 */
    int syscall = 7; 

    struct  procent *prptr = &proctab[getpid()];; /* Pointer to proc. table entry */
    //pruserstack = prptr->prstkbase; /* Get the top of user stack */
    prkstack = prptr->prsyscallkstack; /* Get the top of kernel stack */


    /* Move system call number into EBX */
    /* Move first argument into ECX */
    /* Move second argument into EDX */

    asm("movl %1, %%ebx\n\t"
        "movl %2, %%ecx\n\t"
        "movl %3, %%edx\n\t"
        "int $33 \n\t"
        "movl %%eax, %0\n\t"
        : "=r" (oldprio)
        : "g" (syscall), "g" (pid), "g" (newprio)
        : "%ebx", "%ecx", "%edx", "%esi", "%edi");
    /* : Output Operand */
    /* : Input Operand - syscall number and pid*/
    /* : Adding EBX and ECX into clobber list */
        /* Using the clobber list obviates the need to save/restore register values used by the system call dispatcher. */
    return oldprio;
}

/* listancestorsx.c - listancestorsx */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  listancestorsx  -  Output all ancestor processes and returned their number
 *------------------------------------------------------------------------
 */
syscall listancestorsx(pid32 pid) {
    /* Move system call number into EBX */
    /* Move first argument into ECX*/
    /* Adding EBX and ECX into clobber list */
        /* Using the clobber list obviates the need to save/restore register values used by the system call dispatcher. */
    asm("movl listancestors, %ebx\n\t"
        "movl pid, %ecx\n\t"
        :"%ebx, %ecx");
    asm("int $33");
    return OK;
}
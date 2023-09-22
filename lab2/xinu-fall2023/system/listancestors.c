/* listancestors.c - listancestors */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  listancestors  -  Output all ancestor PIDs of given PID
 *------------------------------------------------------------------------
 */
int32   listancestors(pid32     pid)
{

        if (pid == 0) return 0;

        int32   numancestor = 0;        /* Number of ancestor processes */
        struct  procent *prptr; /* Pointer to proc. table entry */
        int32   ppid;   /* PID of parent process */

        /* Keep looping until the ppid is 0 */
        while ( 1 ) {
                 /* No ppid yet, get process table of pid */
                if (numancestor == 0) {
                        prptr = &proctab[pid];
                } else {
                        /* Get process table of ppid */
                        prptr = &proctab[ppid];
                }
        
        /* Get the parent id */
        ppid = prptr->prparent;

                numancestor++;
                kprintf("Ancestor process ID of PID %d: %d\n", pid, ppid);

                if (ppid == 0) {
                        break;
                }

        }

        return numancestor;
}
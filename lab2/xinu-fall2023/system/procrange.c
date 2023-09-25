/* procrange.c - procrange */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procrange  -   Returns the number of processes in the process table are within range
 *------------------------------------------------------------------------
 */
syscall   procrange(uint16 proc_type, pid32 pid_min, pid32 pid_max)
{
    // check if arguments are invalid
    if (proc_type < 0 || proc_type > 2 || pid_max < pid_min) {
        return SYSERR;
    }
    
    // proc_type == 0 -> ready process, PR_READY
    // proc_type == 1 -> sleep process, PR_SLEEP
    // proc_type == 2 -> suspended process, PR_SUSP

    uint16 proc_check;
    syscall num_proc = 0;

    if (proc_type == 0) {
        proc_check = PR_READY;
    } else if (proc_type == 1) {
        proc_check = PR_SLEEP;
    } else if (proc_type == 2) {
        proc_check = PR_SUSP;
    }
    
    struct  procent *prptr; 
    int pid;
    for (pid = pid_min; pid <= pid_max; pid++) {
        prptr = &proctab[pid];
        if (prptr->prstate == proc_check) {
            num_proc++;
        }
    }

    return num_proc;

        
}
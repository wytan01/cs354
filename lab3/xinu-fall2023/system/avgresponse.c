/*  avgresponse.c  - avgresponse */

#include <xinu.h>

syscall	avgresponse(pid32 pid) {
    /* Check if PID is valid */
    if (isbadpid(pid)) {
        return SYSERR;
    }

    struct procent	*prptr = &proctab[pid];
    syscall avg_response = (prptr->prtotresp + prptr->prtotready - 1) / prptr->prtotready; /* To round up the integer division */

    return avg_response;
}
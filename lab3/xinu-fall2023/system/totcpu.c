/*  totcpu.c  - totcpu */

#include <xinu.h>

extern uint32 cputime;

syscall	totcpu(pid32 pid) {
    /* Check if PID is valid */
    if (isbadpid(pid)) {
        return SYSERR;
    }

    struct procent	*prptr = &proctab[pid];
    syscall total_cpu = prptr->prtotcpu;
    
    if (prptr->prstate == PR_CURR) {
        total_cpu += cputime;
    } 

    return total_cpu;
}
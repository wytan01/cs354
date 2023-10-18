/* cpuproc.c - cpuproc */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cpuproc  - CPU-bound app
 *------------------------------------------------------------------------
 */
void    cpuproc(void) {
    while (clkcountermsec <= STOPCOND) {}  /* Check if it exceeds the threshold */

    intmask	mask = disable();
    kprintf("PID: %d, CPU-bound process, CPU usage: %d, Response time: %d, clkcountermsec: %d\n", currpid, totcpu(currpid), avgresponse(currpid), clkcountermsec);
    restore(mask);

    kill(currpid);  /* Terminate the process*/
}
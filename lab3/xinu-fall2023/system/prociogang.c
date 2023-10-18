/* prociogang.c - prociogang */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  prociogang  - I/O-bound app that starves CPU-bound
 *------------------------------------------------------------------------
 */
void    prociogang(void) {
    /* Check if it exceeds the threshold */
    while (clkcountermsec <= STOPCOND) {
        int i;
        int a = 5;
        /* Consumes 3 msec */
        for (i = 0; i < 5000; i++) {
            a += 2;
        } 
        sleepms(3);
    } 
    intmask	mask = disable();
    kprintf("PID: %d, I/O-bound process, CPU usage: %d, Response time: %d, clkcountermsec: %d\n", currpid, totcpu(currpid), avgresponse(currpid), clkcountermsec);
    restore(mask);
    
    kill(currpid);  /* Terminate the process*/
}
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

        for (i = 0; i < 100000; i++) {
            a += 2;
        } 
        sleepms(2);
    } 
    kprintf("PID: %d, Starving I/O-bound process, CPU usage: %d, Response time: %d, clkcountermsec: %d\n", currpid, totcpu(currpid), avgresponse(currpid), clkcountermsec);
}
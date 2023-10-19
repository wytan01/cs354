/* procio.c - procio */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procio  - I/O-bound app
 *------------------------------------------------------------------------
 */
void    procio(void) {
    /* Check if it exceeds the threshold */
    while (clkcountermsec <= STOPCOND) {
        int i;
        int a = 5;
        /* Consumes 3 msec */
        for (i = 0; i < 5000; i++) {
            a += 2;
        } 
        sleepms(50);    /* Block for 50 ms*/
    } 
    kprintf("PID: %d, I/O-bound process, CPU usage: %d, Response time: %d, clkcountermsec: %d\n", currpid, totcpu(currpid), avgresponse(currpid), clkcountermsec);
}
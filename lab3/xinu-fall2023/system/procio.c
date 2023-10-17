/* procio.c - procio */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procio  - I/O-bound app
 *------------------------------------------------------------------------
 */
void    procio(void) {
    /* Check if it exceeds the threshold */
    while (clkcountermsec <= STOPCOND) {
        int i = 0;
        for (i = 0; i < 100; i++) {}    /* Consumes 2 msec */
        sleepms(50);    /* Block for 50 ms*/
    } 

    kprintf("PID: %d, I/O-bound process, CPU usage: %d, Response time: %d, clkcountermsec: %d\n", currpid, totcpu(currpid), avgresponse(currpid), clkcountermsec);
    
    kill(currpid);  /* Terminate the process*/
}
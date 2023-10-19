/* parasite.c - parasite */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  parasite  - Appears to kernel as I/O-bound but has CPU-bound behavior
 *------------------------------------------------------------------------
 */
void    parasite(void) {
    /* Check if it exceeds the threshold */
    while (clkcountermsec <= STOPCOND) {
        int i;
        int a = 5;
        /* Consumes 3 msec */
        for (i = 0; i < 40000; i++) {
            a += 2;
        } 
        sleepms(0);    /* Kernel interprets as being I/O-bound */
    } 

    kprintf("PID: %d, Parasite I/O-bound process, CPU usage: %d, Response time: %d, clkcountermsec: %d\n", currpid, totcpu(currpid), avgresponse(currpid), clkcountermsec);
    
}
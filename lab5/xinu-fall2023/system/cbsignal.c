/* cbsignal.c - cbsignal */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cbsignal  -  Registers a user callback function with the kernel
 *------------------------------------------------------------------------
 */
syscall	cbsignal(uint16 etype, void (* cbf) (void), uint32 val) {
    if (etype == 1) { // alarm event
        /* Check that timer is not longer than 5s & have only 1 alarm */
        if (val > 5000 || proctab[currpid].pralarmreg != 0) {
            return SYSERR;
        } 

        /* Check that cbf does not fall outside the text segment */
        if ((uint32) cbf < (uint32) &text || (uint32) cbf > (uint32) &etext) {
            return SYSERR;
        }

        proctab[currpid].pralarmreg = 1; // register alarm event
        proctab[currpid].prcbf1 = cbf; // set callback function
        proctab[currpid].pralarmtime = clkcountermsec + val; // set alarm timer

    } else if (etype == 2) { // asynchronous message receive event
        /* Check that cbf does not fall outside the text segment */
        if ((uint32) cbf < (uint32) &text || (uint32) cbf > (uint32) &etext) {
            return SYSERR;
        }

        /* Check that we have only one outstanding message event */
        if (proctab[currpid].prmsgreg != 0) {
            return SYSERR;
        }

        proctab[currpid].prmsgreg = 1;
        proctab[currpid].prcbf2 = cbf;
        if (proctab[currpid].pralarmreg == 0) {
            proctab[currpid].pretype = 2;
        } else if (proctab[currpid].pralarmreg == 1) {
            proctab[currpid].pretype = 3;
        }

    } else {
        return SYSERR;
    }
    return 0;
} 
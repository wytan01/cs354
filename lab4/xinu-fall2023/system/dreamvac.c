/* dreamvac.c - dreamvac */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  dreamvac  -  Kernel to arrange for a detour when it returns from sleepms()
 *------------------------------------------------------------------------
 */

syscall dreamvac(void (* vacation) (void)) {
    // makes current process detour to vacation when returning from sleepms
    proctab[currpid].detourptr = (char *) vacation;
    return OK;
}  
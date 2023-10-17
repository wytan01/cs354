/*  main.c  - main */

#include <xinu.h>

void    donothing(void) {
    int i = 0; 
	for( i = 0; i < 10; i++ ) {
        kprintf("cpu usage in resume pid %d: %d, clkcountermsec: %d\n", getpid(), totcpu(getpid()), clkcountermsec);
    }
}

process	main(void)
{
    /* Test for 3.1 */
    // pid32 p1 = create(donothing, 1024, 20, "proc1", 0, NULL);
    // resume(p1);

    // pid32 p2 = create(donothing, 1024, 30, "proc2", 0, NULL);
    // resume(p2);
    

    // pid32 p3 = create(foo, 1024, 20, "proc3", 0, NULL);

	// pid32 p4 = create(foo, 1024, 20, "proc3", 0, NULL);

    // kprintf("cpu usage before loop: %d, clkcountermsec: %d\n", totcpu(getpid()), clkcountermsec);
    // uint32 goal = clkcountermsec + 5;
    // while( wallclkterm(goal) )
    // kprintf("cpu usage after loop: %d, clkcountermsec: %d\n", totcpu(getpid()), clkcountermsec);
    // make processes with diff priorities and test with them

    chprio(currpid, 3); /* Set main's priority to 3 */
	return OK;
    
}

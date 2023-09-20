/*  main.c  - main */

#include <xinu.h>

void 	proc(void), sndA(void), sndB(void), sndC(void), sndD(void);

process	main(void)
{
    
   	kprintf("Test process: executing main() in process %d\n", getpid());

	/*int procpid = createppid(helloworld, 1032, 10, 2, "proc test", NULL);
	resume(procpid);
	kprintf("procpid: %d, parent pid: %d\n", procpid, proctab[procpid].prparent);
	*/


	/* Testing for listancestors() */
	kprintf("Ancestors for main: %d\n", listancestors(0) );
	
	/* Testing for 3.2 and 4.2 */
	/*resume( create(sndA, 1024, 20, "process 1", 0) );
	resume( create(sndB, 1024, 20, "process 2", 0) );
	resume( create(sndC, 1024, 20, "process 3", 0) );
	resume( create(sndD, 1024, 20, "process 4", 0) );

	kprintf("Printing after snd function\n");*/

	/* Testing for addsubC.S */
	/*kprintf("\nTEST FOR ADDSUB\n");*/

	int sum = addsub(1, 2, 4);
	int sub = addsub(0, 2, 4);
	int err = addsub(2, 2, 4);

	/*kprintf("\n arg1: 2, arg2: 4, sum: %d, sub: %d, err: %d\n", sum, sub, err);

	kprintf("\n TEST FOR ADDSUBC \n");
	sum = testaddsubC(1, -2, -4);
    sub = testaddsubC(0, -2, -4);
    err = testaddsubC(2, -2, -4);

    kprintf("\n arg1: -2, arg2: -4, sum: %d, sub: %d, err: %d\n", sum, sub, err);
	
	sum = addsub(1, -3, 2);
    sub = addsub(0, 3, 2);
    err = addsub(2, -3, 2);

    kprintf("\n arg1: -3/3, arg2: 2, sum: %d, sub: %d, err: %d\n", sum, sub, err);

	kprintf("---------------------");
	kprintf("\n TEST FOR ADDSUBV2 \n");*/

	/* Testing for addsubv2.S */
	int *sump = 0;
	int *subp = 0;
	int *errp = 0;
	//kprintf("before sump addr: %p, subp addr: %p, errp addr: %p\n", sump, subp, errp);
	sum = addsubv2(1, 2, 4, sump);
	kprintf("\nADDITION arg1: 2, arg2: 4, sum: %d, sump: %d\n", sum, *sump);

	sub = addsubv2(0, 2, 4, subp);
	kprintf("\nSUBTRACTION arg1: 2, arg2: 4, sub: %d, subp: %d\n", sub, *subp);
	//kprintf("\nADDITION arg1: 2, arg2: 4, sum: %d, sump: %d\n", sum, *sump);
    
	
	err = addsubv2(2, 2, 4, errp);
	//kprintf("after sub -  sump addr: %p, subp addr: %p, errp addr: %p\n", sump, subp, errp);
	kprintf("\nERROR  arg1: 2, arg2: 4, err: %d, errp: %d\n", err, *errp);
	/*
    kprintf("\n arg1: 2, arg2: 4, sumr: %d, sump: %d,subr: %d, subp: %d, errr: %d, errp: %d\n", sum, *sump, sub, *subp, err, *errp);

	sum = addsubv2(1, -2, -4, sump);
    sub = addsubv2(0, -2, -4, subp);
    err = addsubv2(2, -2, -4, errp);

    kprintf("\n arg1: -2, arg2: -4, sumr: %d, sump: %d,subr: %d, subp: %d, errr: %d, errp: %d\n", sum, *sump, sub, *subp, err, *errp);

	sum = addsubv2(1, -3, 2, sump);
    sub = addsubv2(0, 3, 2, subp);
    err = addsubv2(2, -3, 2, errp);

    kprintf("\n arg1: -3/3, arg2: 2, sumr: %d, sump: %d,subr: %d, subp: %d, errr: %d, errp: %d\n", sum, *sump, sub, *subp, err, *errp);
	*/
	/* Testing for clkcountermsec */
	/*int32 prevclktime = 0;
    int32 prevclkcountermsec = 0;

    while (1) {
        // Check if clktime and clkcountermsec are updated
        if (clktime != prevclktime || clkcountermsec != prevclkcountermsec ) {
            // Update previous values
            prevclktime = clktime;
            prevclkcountermsec = clkcountermsec;

            // Print the current values 
            kprintf("clktime: %d seconds, clkcountermsec: %d milliseconds\n", clktime, clkcountermsec);
        }
    }*/

	return OK;
    
}

void proc(void) {
	kprintf("process running with pid %d\n", getpid());
	sleep(100);
}

void	sndA(void) {
	while( wallclkterm(5000) ) 
			kputc('A');
}

void	sndB(void) {
	while( wallclkterm(5000) )
			kputc('B');
}

void	sndC(void) {
	while( wallclkterm(5000) )
			kputc('C');
}

void	sndD(void) {
	while( wallclkterm(5000) )
			kputc('D');
}

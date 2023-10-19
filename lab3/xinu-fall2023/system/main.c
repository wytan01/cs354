/*  main.c  - main */

#include <xinu.h>

void    donothing(void) {
    int i = 0; 
    int a = 5;
    int b = 6;

	for( i = 0; i < 500000; i++ ) {
        a += b;
    }
    kprintf("cpu usage of pid %d: %d, response time: %d\n", getpid(), totcpu(getpid()), avgresponse(getpid()));
}

process	main(void)
{
    /* Test for 3.1 */
    // donothing();

    // pid32 p1 = create(donothing, 1024, 20, "proc1", 0, NULL);
    // resume(p1);
    // kprintf("cpu usage of pid %d: %d\n", p1, totcpu(p1));

    // pid32 p2 = create(donothing, 1024, 30, "proc2", 0, NULL);
    // resume(p2);
    
    /* Test for 3.2 */
    // kprintf("response time of main before p1: %d\n", avgresponse(getpid()));
    // pid32 p1 = create(donothing, 1024, 25, "proc1", 0, NULL);
    // resume(p1);
    // kprintf("response time of main after p1: %d\n", avgresponse(getpid()));

    // pid32 p2 = create(donothing, 1024, 25, "proc1", 0, NULL);
    // resume(p2);
    // kprintf("response time of main after p2: %d\n", avgresponse(getpid()));

    // pid32 p3 = create(donothing, 1024, 25, "proc1", 0, NULL);
    // resume(p3);
    // kprintf("response time of main after p3: %d\n", avgresponse(getpid()));
    // kprintf("------------------------------------\n");

    // pid32 p4 = create(donothing, 1024, 5, "proc1", 0, NULL);
    // resume(p4);

    // pid32 p5 = create(donothing, 1024, 10, "proc1", 0, NULL);
    // resume(p5);

    // pid32 p6 = create(donothing, 1024, 15, "proc1", 0, NULL);
    // resume(p6);


    /* Test for 4.3 - Benchmark Testing */
    chprio(currpid, 3); /* Set main's priority to 3 */

    /* Benchmark A */
    // pid32 cpu1 = create(cpuproc, 1024, 1, "cpu 1", 0, NULL);
    // pid32 cpu2 = create(cpuproc, 1024, 1, "cpu 2", 0, NULL);
    // pid32 cpu3 = create(cpuproc, 1024, 1, "cpu 3", 0, NULL);
    // pid32 cpu4 = create(cpuproc, 1024, 1, "cpu 4", 0, NULL);

    // resume(cpu1);
    // resume(cpu2);
    // resume(cpu3);
    // resume(cpu4);
    
    /* Benchmark B */
    // pid32 io1 = create(procio, 1024, 2, "io 1", 0, NULL);
    // pid32 io2 = create(procio, 1024, 2, "io 2", 0, NULL);
    // pid32 io3 = create(procio, 1024, 2, "io 3", 0, NULL);
    // pid32 io4 = create(procio, 1024, 2, "io 4", 0, NULL);

    // resume(io1);
    // resume(io2);
    // resume(io3);
    // resume(io4);

    /* Benchmark C */
    // int i;
    // int a = 5;
    // /* Consumes 3 msec */
    // kprintf("clkcountermsec before: %d\n", clkcountermsec);
    // for (i = 0; i < 5000; i++) {
    //     a += 2;
    // } 
    // kprintf("clkcountermsec after: %d\n", clkcountermsec);
    // pid32 cpu1 = create(cpuproc, 1024, 1, "cpu 1", 0, NULL);
    // pid32 cpu2 = create(cpuproc, 1024, 1, "cpu 2", 0, NULL);
    // pid32 cpu3 = create(cpuproc, 1024, 1, "cpu 3", 0, NULL);
    // pid32 cpu4 = create(cpuproc, 1024, 1, "cpu 4", 0, NULL);
    // pid32 io1 = create(procio, 1024, 2, "io 1", 0, NULL);
    // pid32 io2 = create(procio, 1024, 2, "io 2", 0, NULL);
    // pid32 io3 = create(procio, 1024, 2, "io 3", 0, NULL);
    // pid32 io4 = create(procio, 1024, 2, "io 4", 0, NULL);

    // resume(cpu1);
    // resume(cpu2);
    // resume(cpu3);
    // resume(cpu4);
    // resume(io1);
    // resume(io2);
    // resume(io3);
    // resume(io4);

    /* Benchmark D */
    // pid32 cpu1 = create(cpuproc, 1024, 1, "cpu 1", 0, NULL);
    // pid32 cpu2 = create(cpuproc, 1024, 1, "cpu 2", 0, NULL);
    // pid32 cpu3 = create(cpuproc, 1024, 1, "cpu 3", 0, NULL);
    // pid32 ps = create(parasite, 1024, 2, "ps 1", 0, NULL);
    // resume(cpu1);
    // resume(cpu2);
    // resume(cpu3);
    // resume(ps);

    /* Bonus */
    // pid32 io1 = create(prociogang, 1024, 2, "io 1", 0, NULL);
    // pid32 io2 = create(prociogang, 1024, 2, "io 2", 0, NULL);
    // pid32 io3 = create(prociogang, 1024, 2, "io 3", 0, NULL);
    // pid32 cpu = create(cpuproc, 1024, 1, "cpu 1", 0, NULL);
    // resume(io1);
    // resume(io2);
    // resume(io3);
    // resume(cpu);

	return OK;
    
}

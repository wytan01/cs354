/*  main.c  - main */

#include <xinu.h>

extern int divzerocount;

void foo(){
    int32 i = 0;
    while ( 1){
        i++;
    }
}


process	main(void)
{
	/* Test for 3.1: Divide by zero fault */
	// int x = 10, y = 0; 
	// x = x / y;

	/* Test for 3.2: Invalid opcode fault */
	// invalidop6();

	/* Test for 3.3: Generate synchronouse interrupts */
	// int x = 3;
	// asm("int $0");
	// kprintf("%d\n", x);
	// kprintf("divzerocount: %d\n", divzerocount);
	// asm("int $6");
	// kprintf("after synchronous interrupt\n");

	/* Test for 4.2: Software layers*/
	// syscall pid = getpidx();
	// kprintf("in main, pid = %d\n",  pid);
	
	pid32 p1 = create(foo, 1024, 20, "proc1", 0, NULL);
    // resume(p1);

	// syscall oldprio = chpriox(p1, 25);
	// kprintf("in main, oldprio: %d\n", oldprio);

    pid32 p2 = create(foo, 1024, 20, "proc2", 0, NULL);
    // resume(p2);

    pid32 p3 = create(foo, 1024, 20, "proc3", 0, NULL);
    // resume(p3);

	pid32 p4 = create(foo, 1024, 20, "proc3", 0, NULL);

	int i;
	for (i = 0; i <= p4; i++) {
		 struct  procent *prptr = &proctab[i]; 
		kprintf("pid: %d, process state: %d\n", i, prptr->prstate);
	}


	syscall numproc = procrangex(2, 0 , 10);
	kprintf("in main, numproc = %d\n",  numproc);


	return OK;
    
}

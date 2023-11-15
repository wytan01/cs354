/*  main.c  - main */

#include <xinu.h>

void print(void) {
	kprintf("callback\n");
}

void print2(void) {
	kprintf("another callback\n");
}

void testcbf(void) {
	syscall outp1 = cbsignal(1, print, 100);
	syscall outp2 = cbsignal(1, print2, 100);
	kprintf("output 1: %d, output 2: %d\n", outp1, outp2);
	while(1) {
		if (proctab[currpid].pralarmreg == 0) {
			break;
		}
	}
	kprintf("in cbf 1\n");
}

void receiver(void) {
	cbsignal(2, print, 0);
	sleepms(1000);
	kprintf("%d ms: Receive '%s' at pid %d\n", clkcountermsec, receive(), currpid);
}

process	main(void)
{	
    resume(create(testcbf, 1024, 25, "testcbf", 0, NULL));
	pid32 rpid = create(receiver, 1024, 20, "receiver", 0, NULL);
	resume(rpid);
	send(rpid, (umsg32) "hi");
	
	return OK;
}

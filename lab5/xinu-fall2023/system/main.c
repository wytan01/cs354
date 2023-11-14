/*  main.c  - main */

#include <xinu.h>

void print(void) {
	kprintf("callback\n");
}

void print2(void) {
	kprintf("another callback\n");
}

void testcbf(void) {
	cbsignal(1, print2, 100);
	while (1){;}
}

void receiver(void) {
	cbsignal(2, print, 0);
	while(1) {
		sleepms(1000);
		if (proctab[currpid].prhasmsg == TRUE) {
			intmask mask = disable();
			kprintf("%d ms: Receive '%s' at pid %d\n", clkcountermsec, receive(), currpid);
			kprintf("---------------------------\n");
			restore(mask);
		}
	}
}

void sender(pid32 rpid) {
	send(rpid, "hi");
}

process	main(void)
{	
    resume(create(testcbf, 1024, 25, "testcbf", 0, NULL));
	pid32 rpid = create(receiver, 1024, 20, "receiver", 0, NULL);
	resume(rpid);
	resume(create(sender, 1024, 25, "sender", 1, rpid));
	
	return OK;
}

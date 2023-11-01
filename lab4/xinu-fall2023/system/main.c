/*  main.c  - main */

#include <xinu.h>

void sender(umsg32 msg) {
	kprintf("%d ms: Send '%s' from pid %d.... ", clkcountermsec, msg, currpid);
	if (send(4, msg) == OK) {
		kprintf("Sent!\n");
	} else {
		kprintf("Failed to send :( \n");
	}
	kprintf("---------------------------\n");
}

void senderb(umsg32 msg) {
	kprintf("%d ms: Sendb '%s' from pid %d.... ", clkcountermsec, msg, currpid);
	if (sendb(4, msg) == OK) {
		kprintf("Sent!\n");
	} else {
		kprintf("Failed to send :( \n");
	}
	kprintf("---------------------------\n");
	sleepms(40); // to keep the process running
}

void receiver(void) {
	while(1) {
		sleepms(5);
		if (proctab[currpid].prhasmsg == TRUE) {
			intmask mask = disable();
			kprintf("%d ms: Receive '%s' at pid %d\n", clkcountermsec, receive(), currpid);
			kprintf("---------------------------\n");
			restore(mask);
		}
	}
}

void test5(void) {
	dreamvac(vacation);
	sleepms(500);
	kprintf("back in test5\n");
}

process	main(void)
{
	/* Testing for 3: Blocking message send */
	// resume(create(receiver, 1024, INITPRIO, "receiver", 0, NULL));
	// resume(create(sender, 1024, 25, "sender1", 1, "hi"));
	// resume(create(sender, 1024, 25, "sender2", 1, "hello"));
	// resume(create(sender, 1024, 25, "sender3", 1, "hey"));
	// sleepms(10);
	// resume(create(senderb, 1024, 25, "senderb1", 1, "pls"));
	// resume(create(senderb, 1024, 25, "senderb2", 1, "bye"));
	// resume(create(senderb, 1024, 25, "senderb3", 1, "ok"));

	/* Testing for 4: Modifying return address */
	// pid32 vic = create(abc, 1024, 25, "abc_vic", 0, NULL);
	// resume(vic);
	// resume(create(wrongwayhome, 1024, 25, "wrongwayhome", 1, vic));

	/* Testing for 5: Detour */
    // resume(create(test5, 1024, 25, "test5", 0, NULL));
    
	return OK;
}

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

process	main(void)
{	
    resume(create(testcbf, 1024, 25, "testcbf", 0, NULL));
	return OK;
}

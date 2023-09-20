/*  main.c  - main */

#include <xinu.h>

extern int divzerocount;

process	main(void)
{
	/* Test for 3.1: Divide by zero fault */
	// int x = 10, y = 0; 
	// x = x / y;

	/* Test for 3.2: Invalid opcode fault */
	// invalidop6();

	/* Test for 3.3: Generate synchronouse interrupts */
	int x = 3;
	asm("int $0");
	kprintf("%d\n", x);
	kprintf("divzerocount: %d\n", divzerocount);
	asm("int $6");


	return OK;
    
}

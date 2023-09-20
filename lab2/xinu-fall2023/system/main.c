/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	/* Test for 3.1: Divide by zero fault */
	// int x = 10, y = 0; 
	// x = x / y;

	/* Test for 3.2: Invalid opcode fault */
	invalidop6();
	return OK;
    
}

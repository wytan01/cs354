/* sleep.c - sleep sleepms */

#include <xinu.h>

#define	MAXSECONDS	2147483		/* Max seconds per 32-bit msec	*/
// uint32 move;
// char	*detour;
unsigned long  *stack;
unsigned long *ebp;
int offset;

/*------------------------------------------------------------------------
 *  sleep  -  Delay the calling process n seconds
 *------------------------------------------------------------------------
 */
syscall	sleep(
	  int32	delay		/* Time to delay in seconds	*/
	)
{
	if ( (delay < 0) || (delay > MAXSECONDS) ) {
		return SYSERR;
	}
	sleepms(1000*delay);
	return OK;
}

/*------------------------------------------------------------------------
 *  sleepms  -  Delay the calling process n milliseconds
 *------------------------------------------------------------------------
 */
syscall	sleepms(
	  int32	delay			/* Time to delay in msec.	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/

	if (delay < 0) {
		return SYSERR;
	}

	if (delay == 0) {
		yield();
		return OK;
	}

	/* Delay calling process */

	mask = disable();
	if (insertd(currpid, sleepq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}

	proctab[currpid].prstate = PR_SLEEP;

	/* Modify stack here so we won't potentially affect resched and ctxsw's stack too */
	if (proctab[currpid].detourptr != NULL) {
		asm("movl %%esp,%0\n\t"
			"movl %%ebp,%1\n\t"
			: "=r" (stack), "=r" (ebp)
			: 
			:);

		offset = ebp - stack;

		while (offset > 0) {
			*(stack - 1) = *stack;
			stack++;
			offset--;
		}
		*stack = (long) proctab[currpid].detourptr;
		asm("subl $4, %esp"); // to account for moving everything one space down
		asm("subl $4, %ebp"); // to account for moving everything one space down
	}

	resched();

	kprintf("back in sleep\n");

	restore(mask);
	return OK;
}

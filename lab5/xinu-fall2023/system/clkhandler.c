/* clkhandler.c - clkhandler */

#include <xinu.h>

int alarm_flag = 0; // flag to be checked in clkdisp.S
long alarmcbf = 0;	// alarm callback function to be accessed in cbfmanager.S

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Check if the alarm timer for the current process has expired */
	intmask mask = disable();
	if (proctab[currpid].pralarmreg == 1) {
		if (clkcountermsec >= proctab[currpid].pralarmtime) {
			/* Store these in global variables so it can be accessed in .S files */
			alarm_flag = 1;
			alarmcbf = (long) proctab[currpid].prcbf1; 
			proctab[currpid].pralarmreg = 0;	// alarm should be handled directly after, so we can reset it to 0

			/* Update pretype if there's an outstanding asynchronous message event */
			if (proctab[currpid].prmsgreg != 0) { 
				proctab[currpid].pretype = 2;
			}
		}
	} else {
		/* Reset to 0 in case it has been set to 1 and has not been updated */
		alarm_flag = 0;
	}
	restore(mask);

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}

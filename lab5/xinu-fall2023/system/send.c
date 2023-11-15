/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	send(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg) {
		restore(mask);
		return SYSERR;
	}
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/

	if (prptr->prmsgreg == 1) { // checks if it has cbf registered
		unsigned long *stackp = (unsigned long *) prptr->prstkptr; // esp
		unsigned long *ebp = stackp + 2; // where ctxw leaves it
		unsigned long *sleepebp = prptr->prsleepebp;
		int offset = sleepebp - stackp; // to know how much to copy down

		/* Update all ebps until sleepebp */
		while (ebp != sleepebp) {
			unsigned long temp = *ebp; // to record the next ebp to jump to
			*ebp -= 4; // update ebp to account for the moving
			ebp = temp;
		}

		/* Copy the address down until we reach sleepebp */
		while (offset > 0) {
			*(stackp - 1) = *stackp; // copy it down
			stackp++; // move to next address to copy
			offset--; // decrement counter variable
		}

		*(stackp - 1) = *stackp; //	not sure why but sleepebp is not copied down properly 
		*stackp = (long)  prptr->prcbf2; // add detour pointer below RET1	
		prptr->prstkptr -= 4;	// update esp to account for the moving
	}

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}

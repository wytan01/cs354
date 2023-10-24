/* sendb.c - sendb */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendb(
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
        int32 check = enqueuesndb(pid, currpid, msg);
        if (check == SYSERR) { // enqueuesndb failed
            return SYSERR;
        }
        resched();
	} else {
		prptr->prmsg = msg;		/* Deliver message		*/
		prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/

		/* If recipient waiting or in timed-wait make it ready */

		if (prptr->prstate == PR_RECV) {
			ready(pid);
		} else if (prptr->prstate == PR_RECTIM) {
			unsleep(pid);
			ready(pid);
		}
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}

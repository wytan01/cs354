/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;
extern	uint32	cputime;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		ptold->prtotready++; /* Increment since it changed to PR_READY */
		ptold->prreadystart = clkcountermsec; /* Record time it became ready */
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	// preempt = QUANTUM;		/* Reset time slice for process	*/

	/* Set preempt based on process type */
	if (ptnew->prprio == 1) {
		preempt = QUANTUMCPU;
	} else if (ptnew->prprio == 2) {
		preempt = QUANTUMIO;
	} else if (ptnew->prprio == 0) {
		preempt = QUANTUMIDLE;
	} else {
		preempt = QUANTUM;
	}

	/* Update prtotresp using clkcountermsec and prreadystart */
	uint32 diff = clkcountermsec - ptnew->prreadystart;

	if (diff == 0) {
		diff = 1;
	}
	ptnew->prtotresp += diff;

	/* Update the old process' prtotcpu */
	if (cputime == 0) {
		cputime = 1;	/* Round up if it's less than 1 msec */
	}

	ptold->prtotcpu += cputime; /* Update the old process' prtotcpu */
	cputime = 0;	/* Reset to 0 for the new process */

	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}

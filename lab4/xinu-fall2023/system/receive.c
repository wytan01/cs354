/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}

	msg = prptr->prmsg;;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/

	/* Checks if there are blocked sender processes */
	if (prptr->prsendbqueue1 != NULL) {
		uint32 size = sizeof(struct blockedsenders);
		struct blockedsenders *dummyvar = (struct blockedsenders *)getmem(size);

		dequeuesndb(currpid, dummyvar);

		/* Copies to prmsg and set the flag prhasmsg */
		prptr->prmsg = dummyvar->sendermsg;
		prptr->prhasmsg = TRUE;

		/* Changes sender's state & insert into readylist */
		proctab[dummyvar->senderpid].prstate = PR_READY;
		ready(dummyvar->senderpid);
	}

	restore(mask);
	return msg;
}

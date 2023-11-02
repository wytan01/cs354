/* wakeup.c - wakeup */

#include <xinu.h>

extern unsigned long *sleepebp;

/*------------------------------------------------------------------------
 *  wakeup  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */
void	wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */

	resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
		pid32 wakepid = dequeue(sleepq);
		if (proctab[wakepid].detourptr != NULL) {
			unsigned long *stackp = (unsigned long *) proctab[wakepid].prstkptr; // esp
			unsigned long *ebp = stackp + 2; // where ctxw leaves it
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
				offset--;
			}
			*(stackp - 1) = *stackp; //	not sure why but sleepebp is not copied down properly 
			*stackp = (long) proctab[wakepid].detourptr; // add detour pointer below RET1	
			proctab[wakepid].prstkptr -= 4;	// update esp to account for the moving
		}
		ready(wakepid);
	}

	resched_cntl(DEFER_STOP);
	return;
}

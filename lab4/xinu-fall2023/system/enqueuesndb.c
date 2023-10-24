/* enqueuesndb.c - enqueuesndb */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  enqueuesndb  -  Inserts a 1-word message pmessage from sender psender into the FIFO queue of receiver preceiver
 *------------------------------------------------------------------------
 */

enqueuesndb(pid32 preceiver, pid32 psender, umsg32 pmessage) {
    /* Check if pid is valid for sender & receiver */
    if ( isbadpid(preceiver) || isbadpid(psender) ) {
        return SYSERR; // -1 since it fails
    }

    /* Setup pointers */
    struct	procent *receiver_ptr = &proctab[preceiver];

    /* Allocate memory for the new blockedsender structure */
    uint32 size = sizeof(struct blockedsenders);
    struct blockedsenders *newbs = (struct blockedsenders *)getmem(size);

    if (newbs == NULL) { // getmem failed
        return SYSERR;
    }

    /* Initialize struct */
    newbs->senderpid = psender;
    newbs->sendermsg = pmessage;
    newbs->next = NULL;

    /* Check if there's a FIFO queue */
    if (receiver_ptr->prsendbqueue1 == NULL) {
        receiver_ptr->prsendbqueue1 = newbs;
        receiver_ptr->prsendbqueue2 = newbs;
    } else { // there's an existing queue
        /* Insert the new blockedsender into preceiver's queue */
        receiver_ptr->prsendbqueue2->next = newbs;
        /* Update the tail pointer */
        receiver_ptr->prsendbqueue2 = newbs;
    }

    return 0; // Returns 0 upon success
}
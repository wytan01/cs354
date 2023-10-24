/* dequeuesndb.c - dequeuesndb */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  dequeuesndb  -  Retrieve the PID and message of the sender at the front of the FIFO queue
 *------------------------------------------------------------------------
 */

void dequeuesndb(pid32 preceiver, struct blockedsenders *dummystore) {
    /* Get sender at front of queue */
    struct blockedsenders *head = proctab[preceiver].prsendbqueue1;

    /* Update dummy store */
    dummystore->senderpid = head->senderpid;
    dummystore->sendermsg = head->sendermsg;

    /* Update head pointer */
    proctab[preceiver].prsendbqueue1 = head->next;

    /* Free the linked list element */
    freemem((char*) head, sizeof(struct blockedsenders));
}
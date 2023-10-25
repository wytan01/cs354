/* wrongwayhome.c - wrongwayhome */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wrongwayhome - Attacker function that modifies a PID's return address
 *------------------------------------------------------------------------
 */

void wrongwayhome(pid32 vic) {
    uint32 *stack = (uint32 *) proctab[vic].prstkptr; // gets the stack pointer
    stack = stack + 8 + 1 + 1; // pushal, pushfl (EFLAGS), pushl ebp
    *stack = (long)curveball; // overwrite return address
}
/* curveball.c - curveball */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  curveball  -  Function called by attacker, wrongwayhome()
 *------------------------------------------------------------------------
 */

void curveball(void) {
    kprintf("This is a curveball\n");
    exit(); // Terminates process vic
}
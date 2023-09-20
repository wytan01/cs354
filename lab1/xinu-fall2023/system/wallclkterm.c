/* wallclkterm.c - wallclkterm */

#include <xinu.h>

/*------------------------------------------------------------------------
 * wallclkterm - Terminates process if clkcountermsec is >= the time limit
 *------------------------------------------------------------------------
 */
uint32	wallclkterm(uint32 limit)
{
	uint32	difference = 0; /* the difference to be returned */

	if ( clkcountermsec < limit ) {
		difference = limit - clkcountermsec;
	} else {
		exit();
	}

	return difference;
}

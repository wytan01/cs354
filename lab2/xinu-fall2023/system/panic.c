/* panic.c - panic */

#include <xinu.h>

/*------------------------------------------------------------------------
 * panic  -  Display a message and stop all processing
 *------------------------------------------------------------------------
 */
void	panic (
	 char	*msg			/* Message to display		*/
	)
{
	disable();			/* Disable interrupts		*/
	kprintf("clktime: %d seconds\n", clktime);
	kprintf("\n\n\rpanic: %s\n\n", msg);
	while(TRUE) {;}			/* Busy loop forever		*/
	kprintf("clktime after hang: %d seconds\n", clktime);
}

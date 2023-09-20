/* addsubC.c - addsubC */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  addsubC  -  Add or subtract two variables
 *------------------------------------------------------------------------
 */
int	addsubC(
	  int		type,		/* Type of arithmetic operation 	*/
	  int		operand1,	/* Operand 1 for the arithmetic operation	*/
	  int		operand2	/* Operand 2 for the arithmetic operation	*/
	)
{
	int result;

	if (type == 1) {
		result = operand1 + operand2;
	} else if (type == 0) {
		result = operand2 - operand1;
	} else {
		result = -1;
	}

	return result;
}

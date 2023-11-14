/* cbfmanager.s - cbfmanager (x86) */

/*------------------------------------------------------------------------
 * cbfmanager  -  Calls the user callback function
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
        .extern alarmcbf    # Global var for currpid's callback func
		.globl	cbfmanager

cbfmanager:
    movl	alarmcbf, %eax  # Store the callback func ptr in EAX
	call	*%eax   # Call the callback function using indirect function call syntax
    popal           # Pop the 8 registers from clkdisp
    ret             # clkdisp's EIP should be here, go to og return address of clkdisp
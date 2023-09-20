/* invalidop6.s - invalidop6 (x86) */
#include <icu.s>
    .text
    .globl	invalidop6

/*------------------------------------------------------------------------
 * invalidop6  -  Generates interrupt number 6
 *------------------------------------------------------------------------
 */
invalidop6:
    pushal			    # Save registers
    movl    %ebx, %cr1  # Generates interrupt number 6 because CR 0-8 are off-limits
    popal               # Restore registers
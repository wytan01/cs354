/* clkdisp.s - clkdisp (x86) */

/*------------------------------------------------------------------------
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
		.globl	clkdisp		# Clock interrupt dispatcher
		.extern	cputime		# Global var from initialize.c
		.extern clkcountermsec # global variable from clkinit.c
clkdisp:
		pushal			# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		movl	cputime, %eax 	# move var into eax register
		addl 	$1, %eax		# add 1 to the content of eax
		movl	%eax, cputime 	# move the content of eax back to var

		movl	clkcountermsec, %eax 	# move var into eax register
		addl 	$1, %eax				# add 1 to the content of eax
		movl	%eax, clkcountermsec 	# move the content of eax back to var

		sti			# Restore interrupt status
		popal			# Restore registers
		iret			# Return from interrupt

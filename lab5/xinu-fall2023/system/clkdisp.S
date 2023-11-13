/* clkdisp.s - clkdisp (x86) */

/*------------------------------------------------------------------------
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
		.globl	clkdisp		# Clock interrupt dispatcher
		.extern clkcountermsec # global variable from clkinit.c
		.extern	alarm_flag
clkdisp:
		pushal			# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		movl	alarm_flag, %eax	# Move var into eax register
		cmpl	$1, %eax			# Check if alarm_flag is set
		je		move_stack			# Move stack if it is
		jmp		clkdisp_cont		# Continue with prev code if not

move_stack:
		/* Storing variables */
		movl	%esp, %ecx		# Store esp address in ECX
		movl	36(%esp), %esi	# Store CS in register ESI
		movl	40(%esp), %edi	# Store EFlAGS in register EDI
		movl	$0, %eax		# Store loop counter variable in EAX

		/* Setting up pointers to copy stuff to and from each other */
		addl	$32, %ecx		# Move the pointer to address storing EIP, i.e.,  the starting point for where we copy stuff from
		movl	%ecx, %edx
		addl	$8, %edx			# Move the pointer to address storing EFLAGS, i.e., the starting point for where we copy stuff to

		jmp		move_loop		# Jump to label that loops the moving stack stuff

move_loop:
		cmpl	$9, %eax		# Check if we have moved everything further down the stack
		je		cleanup			# Move to cleanup if we're done
		movl	(%ecx), %ebx	# Store content at address in ECX to EBX
		movl	%ebx, (%edx)	# Store content at EBX to address in EDX
		subl	$4, %ecx		# Set the pointer for the next address to copy
		subl	$4, %edx 		# Move the destination address down
		
		addl	$1, %eax		# Increment loop counter variable
		jmp		move_loop		# Return to start of loop

cleanup:
		/* Stack should be (bottom) EIP -> 8 regs. (top) right now */
		movl	%edi, %ebx	# Store EFLAGS in register EBX
		movl	%ebx, (%edx)	# Store content at EBX to address in EDX
		subl	$4, %edx 		# Move the destination address down

		movl	%esi, %ebx	# Store CS in register EBX
		movl	%ebx, (%edx)	# Store content at EBX to address in EDX
		subl	$4, %edx 		# Move the destination address down

		/* Stack should be (bottom) EIP -> 8 regs. -> EFLAGS -> CS (top) right now */
		pushl	$cbfmanager		# Add cbfmanager's function ptr to stack
								# Should update ESP since we're using pushl

		/* Continue with normal clkdisp stuff */
		movl	clkcountermsec, %eax 	# move var into eax register
		addl 	$1, %eax				# add 1 to the content of eax
		movl	%eax, clkcountermsec 	# move the content of eax back to var

		sti			# Restore interrupt status
		iret		# Return from interrupt. No popal because we do that in cbfmanager.S
 


clkdisp_cont:		
		mov		clkcountermsec, %eax 	# move var into eax register
		add 	$1, %eax				# add 1 to the content of eax
		mov		%eax, clkcountermsec 	# move the content of eax back to var

		sti			# Restore interrupt status
		popal			# Restore registers
		iret			# Return from interrupt

/* Name: Wei Yi Tan, Username: wytan */

        .text
        .globl testaddsubC

testaddsubC:
        pushl   %ebp		# Save the old base pointer value
		# base pointer is a reference for params and local vars on the stack
        movl    %esp,%ebp	# Set the new base pointer value

		pushl	%ebx		# Save ebx register value

		movl	16(%ebp), %ebx	# Move param 3 into ebx
        movl	12(%ebp), %ecx 	# Move param 2 into ecx
        movl	8(%ebp), %edx 	# Move param 1 into edx

		pushl	%ebx		# push param 3 onto stack first
		pushl	%ecx		# push param 2 onto stack 
		pushl	%edx		# push param 1 onto stack last

		call	addsubC		# Call function addsubC()

		addl	$12, %esp	# Clean up the stack by moving stack pointer
		
		popl	%ebx		# Restore ebx register value

        movl    (%esp),%ebp # recover ebp value
        addl    $4,%esp		# adjusts the stack pointer & deallocate space
        ret 				# return the value in %eax

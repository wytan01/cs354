/* Name: Wei Yi Tan, Username: wytan */

        .text
        .globl addsub

addsub:
        pushl   %ebp		# Save the old base pointer value
		# base pointer is a reference for params and local vars on the stack
        movl    %esp,%ebp	# Set the new base pointer value

        movl    8(%ebp),%edx 	# Move value of param 1 into edx
        movl    12(%ebp),%ecx 	# Move value of param 2 into ecx
		movl	16(%ebp), %eax 	# Move value of param 3 into eax

		cmp		$1, %edx	# Check if param 1 == 1
		je		sum			# sum param 2 and 3 if param 1 == 1
		cmp 	$0, %edx	# Check if param 1 == 0
		je	 	sub			# subtract param 2 from param 3 if param 1 == 0
		jmp		negone		# set return value to -1 if param 1 != 0 or != 1

negone:
		movl	$-1, %eax	# set return value to -1, result is stored in eax
		jmp		done		# jump to done label
				
sum:
		addl	%ecx, %eax	# sum param 2 and param 3, result is stored in eax
		jmp		done		# jump to done label

sub:
		subl	%ecx, %eax	# subtract param 2 from param 3
		jmp		done		# jump to done label

done:
        movl    (%esp),%ebp # recover ebp value
        add     $4,%esp		# adjusts the stack pointer & deallocate space
        ret 				# return the value in %eax

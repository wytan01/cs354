/* Name: Wei Yi Tan, Username: wytan */

        .text
        .globl addsubv2

/* int addsubv2(int, int, int, int*) */

addsubv2:
        pushl   %ebp		# Save the old base pointer value
		# base pointer is a reference for params and local vars on the stack
        movl    %esp,%ebp	# Set the new base pointer value
		pushl	%ebx		# Push ebx on the stack

        movl    8(%ebp),  %eax 	# Move value of param 1 into eax
        movl    12(%ebp), %ebx 	# Move value of param 2 into ebx
		movl	16(%ebp), %ecx 	# Move value of param 3 into ecx
		movl	20(%ebp), %edx	# Move value of param 4 (pointer) into edx

		cmp		$1, %eax	# Check if param 1 == 1
		je		sum			# sum param 2 and 3 if param 1 == 1
		cmp 	$0, %eax	# Check if param 1 == 0
		je	 	sub			# subtract param 2 from param 3 if param 1 == 0
		jmp		negone		# set return value to -1 if param 1 != 0 or != 1

negone:
		movl	$-1, %eax	# set return value to -1, result is stored in eax
		jmp		done		# jump to done label
				
sum:
		addl	%ebx, %ecx	# sum param 2 and param 3, result is stored in eax
		jmp		valid		# jump to valid label

sub:
		subl	%ebx, %ecx	# subtract param 2 from param 3
		jmp		valid		# jump to valid label

valid:
		movl    %ecx,(%edx)	# param 4 now points to the result
        movl    $0, %eax    # set return value to 0, indicate there's a calculation
		jmp done			# jump to done label

done:      
		popl	%ebx		# recover ebx prev value
        movl    (%esp),%ebp # recover ebp value
        add     $4,%esp		# adjusts the stack pointer & deallocate space
        ret 				# return the value in %eax

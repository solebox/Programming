.data
	HelloWorld:
		.asciz "Hellow World!\n"
	HelloFunction:
		.asciz "Hello Function!\n"

.text
	.globl _start
		.type MyFunction, @function
		
		MyFunction: # String pointer and len to be added by caller

			movl $4, %eax
			movl $1, %ebx
			int $0x80
			ret

	_start:
		nop
		#print the hello world string

		leal HelloWorld, %ecx
		movl $14, %edx
		call MyFunction

		#print Hello Function

		leal HelloFunction, %ecx
		movl $17, %edx
		call MyFunction

	ExitCall:	
		movl $1, %eax
		movl $0, %ebx
		int $0x80

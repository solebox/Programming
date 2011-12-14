.data
	HelloWorld:
		.asciz "Hello World!\n"

	CallDemo:
		.asciz "Call works!\n"
.text

	.globl _start

	_start:
		nop
		call CallMe
		#write HelloWorld
			movl $4, %eax 					#the write() system call number
			movl $1, %ebx						# STDOUT
			movl $HelloWorld, %ecx 	# the string
			movl $13, %edx					# size of string
			int $0x80
 
 		ExitProgram:
 		 	# Exiting the Program
 			movl $1, %eax
 			movl $10, %ebx
 			int $0x80
		 
		 CallMe:
		 	movl $4, %eax
			movl $1, %ebx
			movl $CallDemo, %ecx
			movl $12, %edx
			int $0x80
			ret

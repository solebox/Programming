#condigional jumps do not support long(far) jumps only short and near jumps
.data
	HelloWorld:
		.asciz "Hello World!\n"

	ZeroFlagSet:
		.asciz "Zero Flag Was Set!\n"

	ZeroFlagNotSet:
		.asciz "Zero Flag Not Set!\n"

.text
	.globl _start
	_start:
		nop
		movl $10, %eax
		xorl %eax, %eax #sets zero flag since xor(same, same) results in zero
		jz PrintHelloWorld 

	FlagNotSetPrint:
		movl $4, %eax
		movl $1, %ebx
		leal ZeroFlagNotSet, %ecx
		movl $20, %edx
		int $0x80
		jmp ExitCall

	FlagSetPrint:
		movl $4, %eax
		movl $1, %ebx
		leal ZeroFlagSet, %ecx
		movl $20, %edx
		int $0x80
		jmp ExitCall

	ExitCall:
		movl $1, %eax
		movl $0, %ebx
		int $0x80

	PrintHelloWorld:
		movl $10, %ecx
		PrintTenTimes:
			pushq %rcx
			movl $4, %eax
			movl $1, %ebx
			leal HelloWorld, %ecx
			movl $14, %edx
			int $0x80
			popq %rcx
		loop PrintTenTimes
		jmp ExitCall

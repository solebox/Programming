.data
	helloWorldString:
		.ascii "Hello World\n"
	goodbye:
		.ascii "Goodbye World\n"
.text

.globl _start
_start:
	movl $4, %eax # write() syscall code number
	movl $1, %ebx # the STDOUT file descriptor 
	movl $helloWorldString, %ecx
	movl $12, %edx
	int $0x80
	movl $4, %eax
	movl $1, %ebx
	movl $goodbye, %ecx
	movl $14, %edx 
	int $0x80
	movl $1, %eax # exit() syscall code number
	movl $0, %ebx # exit status is 0 ( exit( 0 ) )
	int $0x80 # envoke the syscall

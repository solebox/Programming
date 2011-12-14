.data
	HelloWord:
		.ascii "Hello World!"
		ByteLocation:
			.byte 10
		Int32:
		 .int 2
		Int16:
			.short 3
		Float:
			.float 10.23
		IntegerArray:
			.int 10,20,30,40,50
.bss
	.comm LargeBuffer, 10000
.text
	.globl _start
	_start:
		nop
	# 1. MOV immediate value into register
		movl $10, %eax
	# 2. MOV immediate value into memory location
		movw $50,  Int16
	# 3. MOV data between registers
		movl %eax, %ebx
	# 4. MOV data from memory to register
		movl Int32, %eax
	# 5. MOV data from register to memory
		movb $3, %al
		movb %al, ByteLocation
	# 6. MOV data into an indexed memory location
  # location is decided by BaseAddress(offset, index, datasize)
  # offset and index must be registers, datasize can be of numberical value
		movl $0, %ecx
		movl $2, %edi
		movl $22, IntegerArray(%ecx,%edi,4) 
	# 7. Indirect addressing using registers

		movl $Int32, %eax
		movl (%eax), %ebx
		
		movl $9, (%eax)
  # exit(0)
		mov $1, %eax
		mov $0, %ebx
		int $0x80

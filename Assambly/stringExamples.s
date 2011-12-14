#
#	MOVSx - mem to mem copy (ESI => EDI)
#	MOVSB - move a byte (8 bit) 1 byte
# MOVSW - move a word (16 bit) 2 bytes
# MOVSL - move a double word (32 bits) 4 bytes
# Source ESI Destination EDI
.data
	HelloWorldString:
		.asciz "Hello world of assembly!"
	H3110:
		.asciz "H3110"
.bss
	.lcomm Destination, 100
	.lcomm DestinationUsingRep, 100
	.lcomm DestinationUsingStos, 100
.text
	.globl _start
	_start:
		nop
# 1. Simple copying using movsb, movsw , movsl
		movl $HelloWorldString, %esi
		movl $Destination, %edi
		movsb
		movsw
		movsl
# 2. setting / clearing the DF flag
		std # set the DF flag
		cld # clear the DF flag
# 3. Using Rep
		movl $HelloWorldString, %esi
		movl $DestinationUsingRep, %edi
		movl $25, %ecx # set the string length in ECX
		cld # clear the DF (direction flag) , incremation (DF = 0)
		rep movsb
		std
# LODSx loads into the EAX register a string source pointed to by ESI
# LODSB - load a byte from memory into AL ( 1 byte)
# LODSW - load a word from memory into AX ( 2 bytes)
# LODSL - load a double word from memory into EAX (4 bytes)
# ESI is automatically incremented based on DF flag after LODSx instruction is exec

# 4. Loading string from memory into EAX register

		cld
		leal HelloWorldString, %esi
		lodsb
		movb $0, %al

		dec %esi
		lodsw
		movw $0, %ax
		subl $2, %esi # make ESI point back to the original string
		lodsl
# storing strings from EAX to memory (register to mem)
# EAX - source
# EDI - points to destination memory
#STOSx 
# STOSB/STOSW/STOSL
# EDI incremented if DF = 0 and decremented if DF = 1
# 5. storing strings from EAX to memory
		leal DestinationUsingStos, %edi
		stosb
		stosw
		stosl
# 6. Comparing strings
		cld
		leal HelloWorldString, %esi
		leal H3110, %edi
		cmpsb

		dec %esi
		dec %edi
		cmpsw

		subl $2, %esi
		subl $2, %edi
		cmpsl

# the exit() syscall
	movl $1, %eax
	movl $0, %ebx
	int $0x80

.data 
		stn: db "lala",0

.text
	globl _start
	_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, stn
	mov edx, 5
	int 0x80


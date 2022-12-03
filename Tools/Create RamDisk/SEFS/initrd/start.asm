section .text
global _start
_start:
	mov eax, 0x02
	mov ebx, 0x01
	mov ecx, msg
	int 0x50

	mov eax, 0x02
	mov ebx, 0x01
	mov ecx, msg2
	int 0x50

	mov eax, 0x02
	mov ebx, 0x00
	mov ecx, 'H'
	int 0x50
	
	mov eax, 0x02
	mov ebx, 0x00
	mov ecx, 'i'
	int 0x50
	
	mov eax, 0x02
	mov ebx, 0x00
	mov ecx, 10
	int 0x50


	ret

section .rodata
msg: db "Hello World!!!\n", 0
msg2: db "Another day in paradise...\n", 0

section .text
global _start
_start:
	mov eax, 0x03
	mov ebx, 0x00
	mov edx, msg
	int 0x50
	
	ret

section .data
msg: db "Hello World!!!", 0

section .text
global main
main:
	mov eax, 0x02
	mov ebx, 0x01
	mov ecx, msg
	int 0x50

	mov eax, 0x02
	mov ebx, 0x01
	mov ecx, msg2
	int 0x50

	;mov eax, 0
	ret

section .rodata
msg: db "Hello World!!!", 10, 0
msg2: db "Another day in paradise...", 10, 0

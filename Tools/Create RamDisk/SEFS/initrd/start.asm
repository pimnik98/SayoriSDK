global main
main:
	mov eax, 0x02
	mov ebx, string

	int 0x50

string: db "Hello World from Sash Lilac!!!\n", 0

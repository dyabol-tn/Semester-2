.386
.model flat, C

.data
x dd 0
a dd 0
b dd 0
c1 dd 0
ya dd 0

.code
Public __main_asm
__main_asm proc

push ebp
mov ebp, esp
mov eax, [ebp + 8]
mov x, eax
mov eax, [ebp + 12]
mov a, eax
mov eax, [ebp + 16]
mov b, eax
mov eax, [ebp + 20]
mov c1, eax
mov edi, [ebp + 24]
mov dword ptr [edi], 1

mov eax, x
		imul eax, c1
		jo overflow
		mov ebx, eax
		mov eax, b
		imul eax
		jo overflow
		add ebx, eax
		jo overflow

		mov eax, c1
		imul eax, 4
		jo overflow
		mov ecx, x
		imul ecx, 2
		jo overflow
		test ecx, ecx
		jz zero
		cdq
		idiv ecx;
		add ebx, eax
			jo overflow

			mov eax, x
			imul eax, eax
			jo overflow
			imul eax, 3
			jo overflow
			mov ecx, eax
			mov edx, a
			mov eax, b
			test edx, edx
			jz zero
			cdq
			idiv a
			sub ecx, eax

			mov eax, ebx
			test ecx, ecx
			jz zero
			cdq
			idiv ecx
			mov ya, eax
			jmp done
			overflow :
		mov dword ptr [edi], 0
		xor eax, eax
			jmp done

			zero :
		mov dword ptr [edi], 2
		xor eax, eax

			done :
			mov esp, ebp
			pop ebp
			ret
			__main_asm endp
			end
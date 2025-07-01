.386
.model flat, C

;.data
;x dd 0
;a dd 0
;b dd 0
;c1 dd 0
;ya dd 0

.code
Public __compare_asm
__compare_asm proc

;[ebp + 8] - str1
;[ebp + 12] - num1
;[ebp + 16] - str2
;[ebp + 20] - num2

push ebp
mov ebp, esp
push esi
push edi
push ecx

mov eax, [ebp + 12]
mov ecx, [ebp + 20]
cmp eax, ecx
jne not_equal

mov ecx, [ebp + 12]
mov esi, [ebp + 8]
mov edi, [ebp + 16]

cld
repe cmpsb
jne not_equal
je is_equal
is_equal:
mov eax, 1
;в ecx –количество необработанных байтов
jmp m_end
not_equal:
mov eax, 0
m_end:
mov esp, ebp
pop ebp

			ret
			__compare_asm endp
			end
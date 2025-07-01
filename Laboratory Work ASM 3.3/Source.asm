.code
 ; x -> rcx, a -> rdx, b -> r8, c -> r9, temp -> r10
 ; yc = ((x * c) + (b * b) + ((4 * c) / (2 * x))) / ((3 * x * x) - (b / a))
 __main_asm PROC

    push rbx
    push rsi
   
    mov rsi, [rsp+28h+16]
    mov dword ptr [rsi], 1

 mov r10, 1
 mov rbx, rdx

 mov rax, rcx
 imul r9
 jo overflow
 mov r12, rax
 mov rax, r8
 imul r8
 jo overflow
 mov r13, rax
 add r12, r13
 jo overflow
 mov rax, r9
 imul rax, 4
 jo overflow
 mov r13, rcx
 imul r13, 2
 jo overflow
 test r13, r13
 jz zero
 cqo
 idiv r13
 add r12, rax
 jo overflow

 mov r13, rcx
 imul r13, 3
 jo overflow
 mov rax, r13
 imul rcx
 jo overflow
 mov r13, rax
 mov rax, r8
 test rbx, rbx
 jz zero
 cqo
 idiv rbx
 sub r13, rax

 mov rax, r12
 test r13, r13
 jz zero
 cqo
 idiv r13
 mov rdx, 1
			jmp done
			overflow :
		mov dword ptr [rsi], 0
		xor rax, rax

			jmp done

			zero :
		mov dword ptr [rsi], 2
		xor rax, rax

			done :
			

			pop rsi
			pop rbx

			ret
			__main_asm ENDP
			end
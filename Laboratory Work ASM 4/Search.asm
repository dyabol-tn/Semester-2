.386
.model flat, C

.data
x dd 0
a dd 0
b dd 0
c1 dd 0
ya dd 0

.code
Public __search_asm
__search_asm proc
    push ebp
    mov ebp, esp
    push esi
    push edi
    push ebx
    
    cld
    
    mov edi, [ebp+8]         
    mov ecx, [ebp+12]       
    mov esi, [ebp+16]      
    mov al, [esi]

    mov eax, [ebp + 12]
    mov ebx, [ebp + 20]
    cmp ebx, eax
    jg errsize
    
search_loop:
    repne scasb
    jne m_not
    
    mov ebx, edi
    mov edx, ecx
    
    mov edi, ebx
    mov esi, [ebp+16]
    inc esi
    mov ecx, [ebp+20]
    dec ecx
    jz found
    
    repe cmpsb
    jne m_cont
    
    errsize:
    mov eax, 0
    jmp m_end

found:
    mov eax, 1
    jmp m_end
    
m_cont:
    mov edi, ebx
    mov ecx, edx           
    jmp search_loop
    
m_not:
    mov eax, 2
    
m_end:
    pop ebx
    pop edi
    pop esi
    mov esp, ebp
    pop ebp
    ret
__search_asm endp
end

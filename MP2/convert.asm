section .text
global _imgCvtGrayInttoFloat    

_imgCvtGrayInttoFloat:         
    ; rdi = input (int*)
    ; rsi = output (float*)
    ; rdx = height
    ; rcx = width

    mov eax, edx        ; height
    imul eax, ecx       ; eax = eax * edx
    xor ecx, ecx        ; ecx = 0 (loop counter)

.loop_convert:
    cmp ecx, eax
    jge .end

    mov ebx, dword [rdi + rcx * 4]  
    cvtsi2ss xmm0, ebx             
    movss xmm1, dword [rel floatVal]   
    divss xmm0, xmm1                   
    movss [rsi + rcx * 4], xmm0      

    inc ecx
    jmp .loop_convert

.end:
    ret

section .data
    floatVal dd 255.0

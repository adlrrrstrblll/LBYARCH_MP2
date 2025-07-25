section .data
    floatVal dd 255.0          

section .text
global imgCvtGrayIntToFloat

imgCvtGrayIntToFloat:
    push rbx
    push r12

    mov     rsi, rcx              
    mov     rdi, rdx              
    mov     eax, r8d             
    imul    eax, r9d              
    xor     ebx, ebx              

    movss   xmm1, [rel floatVal]  

divide_loop:
    cmp     ebx, eax
    jge     done

    ; 1st Pixel
    mov     r12d, [rsi + rbx*4]
    cvtsi2ss xmm2, r12d
    divss   xmm2, xmm1
    movss   [rdi + rbx*4], xmm2
    inc     ebx
    cmp     ebx, eax
    jge     done

    ; 2nd Pixel
    mov     r12d, [rsi + rbx*4]
    cvtsi2ss xmm3, r12d
    divss   xmm3, xmm1
    movss   [rdi + rbx*4], xmm3
    inc     ebx
    cmp     ebx, eax
    jge     done

    ; 3rd Pixel
    mov     r12d, [rsi + rbx*4]
    cvtsi2ss xmm4, r12d
    divss   xmm4, xmm1
    movss   [rdi + rbx*4], xmm4
    inc     ebx
    cmp     ebx, eax
    jge     done

    ; 4th Pixel
    mov     r12d, [rsi + rbx*4]
    cvtsi2ss xmm5, r12d
    divss   xmm5, xmm1
    movss   [rdi + rbx*4], xmm5
    inc     ebx
    jmp     divide_loop

done:
    pop r12
    pop rbx
    ret

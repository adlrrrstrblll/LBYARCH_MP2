section .text
global imgCvtGrayIntToFloat

imgCvtGrayIntToFloat:
    MOV RSI, RCX ; intPixels
    MOV RDI, RDX ; floatPixels
    
    MOV EAX, R8d ; height
    IMUL EAX, R9d ; height * width
    MOV ECX, 0 ; index = 0
    
loop_convert:
    CMP ECX, EAX     
    JGE end
    
    MOV EBX, [RSI + RCX * 4]   
    CVTSI2SS XMM0, EBX      
    MOVSS XMM1, [floatVal]     
    DIVSS XMM0, XMM1             ; xmm0 = pixel / 255.0
    MOVSS [RDI + RCX * 4], XMM0

    INC ECX
    JMP loop_convert

end:
    RET
    
section .data 
    floatVal dd 255.0

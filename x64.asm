default rel

section .text
    global x64

; void x64(double* Z, const double* X1, const double* X2,
;         const double* Y1, const double* Y2, int n)
; Windows x64 Calling Convention:
;   RCX: Z (output array)
;   RDX: X1
;   R8:  X2
;   R9:  Y1
;   [rsp+40]: Y2 (5th argument)
;   [rsp+48]: n (6th argument)

x64:
    push rbp
    mov rbp, rsp
    ; Save non-volatile registers we'll use
    push rbx
    push rdi
    push rsi

    ; Load arguments from stack (correct offsets)
    mov rdi, [rbp+48]       ; Y2 (40 shadow + 8 return address)
    mov ebx, [rbp+56]       ; n (32-bit int)

    ; Set up registers for calculation
    mov rsi, rcx            ; Z (output)
    ; RDX already contains X1
    ; R8 already contains X2
    ; R9 already contains Y1

    xor ecx, ecx            ; i = 0

.loop:
    cmp ecx, ebx
    jge .done

    ; Calculate dx = X2[i] - X1[i]
    movsd xmm0, [r8 + rcx*8]
    subsd xmm0, [rdx + rcx*8]
    mulsd xmm0, xmm0        ; dx²

    ; Calculate dy = Y2[i] - Y1[i]
    movsd xmm1, [rdi + rcx*8]
    subsd xmm1, [r9 + rcx*8]
    mulsd xmm1, xmm1        ; dy²

    ; Calculate and store distance
    addsd xmm0, xmm1
    sqrtsd xmm0, xmm0
    movsd [rsi + rcx*8], xmm0

    inc ecx
    jmp .loop

.done:
    pop rsi
    pop rdi
    pop rbx
    pop rbp
    ret
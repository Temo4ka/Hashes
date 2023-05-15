.model flat, stdcall
option casemap: none

HASH_START_CONST equ 1505h
 HASH_MUL_CONST  equ 0021h

;---------------------------------------------------
; int GnuHashMasm86(const char * string)
;===================================================
; Input  : offset to the string
;
; Output :  (EDX:EAX) = hash
;
;Destroys:  R8, R9
;---------------------------------------------------
.code
GnuHashMasm86 proc string:dword

	push ebx
	push ecx

	mov ebx, string

	mov eax, HASH_START_CONST
	xor ecx, ecx
	xor edx, edx

    lp:									; do {
		imul eax, eax, HASH_MUL_CONST	;		ans *= HASH_MUL_CONST

		movsx ecx, byte ptr[ebx]		;
		add eax, ecx 					;		ans += string[ebx]

		lea ebx, [ebx + 1]				;		ebx++

	cmp byte ptr [ebx], 0h				;	
	jne lp								; } while (string[ebx] != 0)
	
	pop ecx
	pop ebx

	ret
GnuHashMasm86 endp

end
;.model flat, stdcall
option casemap: none

HASH_START_CONST equ 1505h
 HASH_MUL_CONST  equ 0021h

;printf proto C :qword, : vararg

;---------------------------------------------------
; int GnuHash(const char * string)
;===================================================
; Input  :  RCX = offset to the string
;
; Output :  RAX = hash
;
;Destroys:  R8, R9
;---------------------------------------------------
.code
GnuHashAsm proc 

	mov r9, rcx

	mov rax, HASH_START_CONST
	xor r8d, r8d
	xor rdx, rdx

    lp:									; do {
		imul rax, rax, HASH_MUL_CONST	;		ans *= HASH_MUL_CONST

		movsx r8, byte ptr[r9]			;
		add rax, r8 					;		ans += string[rcx]

		lea r9, [r9 + 1]				;		rcx++

	cmp byte ptr [r9], 0h				;	
	jne lp								; } while (string[rcx] != 0)
	
	ret
GnuHashAsm endp

end
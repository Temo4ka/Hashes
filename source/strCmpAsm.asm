;.model flat, stdcall
option casemap: none

printf proto C :qword, : vararg

ITERATIONS_NUM equ 3d
     SHIFT	   equ 8d

;---------------------------------------------------
; int strcmpAsm(const char *str1, const char *str2)
;===================================================
; Input : RDX = str1, RCX = str2 
;		  (size of strings should be 32 bytes)
;
; Output : RAX = (equal)? 1 : 0;
;
;---------------------------------------------------
.code
strcmpAsm proc

	mov r14, rcx	; str1
	mov r15, rdx	; str2

	mov r8, 3
		
	lp1:
		mov r9, qword ptr [r14]
		cmp r9, qword ptr [r15]
		jne not_equal

		lea r14, [r14 + SHIFT]
		lea r15, [r15 + SHIFT]
		lea r8,  [r8  -   1  ]

	cmp r8, 0d
	jne lp1
		
	xor rax, rax	;str1 == str2
	jmp end_func
	
	not_equal:
	or rax, 1
		
	end_func:
	ret  
	
strcmpAsm endp

end
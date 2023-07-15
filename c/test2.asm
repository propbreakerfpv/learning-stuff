	.file	"test.c"
	.intel_syntax noprefix
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64                     ; check for hackers. kindof...
	push	rbp                 ; save the address of previous stack frame
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp                ; set rbp to rsp. set the new base pointer
	.cfi_def_cfa_register 6
	mov	DWORD PTR -8[rbp], 65   ; move 65(0x41) to the memory address in rbp - 8 ; x = 0x41
	mov	eax, DWORD PTR -8[rbp]  ; move x (rbp - 8) to eax
	add	eax, 1                  ; add 1 to eax
	mov	DWORD PTR -4[rbp], eax  ; move the value in ezx to the memory address in rbp - 4; y = x + 1
	mov	eax, 0                  ; move 0 to eax ; set return value to 0
	pop	rbp                     ; pop rbp to return to the previous stack frame
	.cfi_def_cfa 7, 8
	ret                         ; return
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:

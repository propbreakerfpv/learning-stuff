	.file	"test.c"
	.intel_syntax noprefix
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	push	rbp                 ; save address of previous stack frame
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp                ; set rbp to rsp. set the new base ointer value
	.cfi_def_cfa_register 6
	mov	DWORD PTR -20[rbp], edi ; move the value in edi to the memory address in rbp - 20 ; ?
	mov	QWORD PTR -32[rbp], rsi ; move the value in rsi to the memory address in rbp - 32 ; ?
	mov	DWORD PTR -8[rbp], 65   ; move 65 (0x41) to the memory address in rbp - 8   ; x = 0x41
	mov	eax, DWORD PTR -8[rbp]  ; mvoe x (rbp - 8) to eax
	add	eax, 1                  ; add 1 to eax
	mov	DWORD PTR -4[rbp], eax  ; mov the value in eax to the memory address in rbp - 4 ; y = x + 1
	mov	eax, 0                  ; move 0 to eax ; ?
	pop	rbp                     ; restor the previous stack frame
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

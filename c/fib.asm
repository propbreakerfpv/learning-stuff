	.file	"fib.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"%i\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64                     ; prevent hackers...
	push	rbp                 ; save the previous stack frame
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp                ; setup for new stack frame
	.cfi_def_cfa_register 6
	sub	rsp, 16                 ; alocate for x y and z ?
	jmp	.L2                     ; jump to L2
.L3:
	mov	eax, DWORD PTR -12[rbp] ; move eax rbp - 12 (x)
	mov	esi, eax                ; move esi eax (value of x)
	lea	rdi, .LC0[rip]          ; address to are string ("%i\n")
	mov	eax, 0                  ; move eax 0
	call	printf@PLT          ; call printf
	mov	edx, DWORD PTR -12[rbp] ; move edx rbp - 12(x)
	mov	eax, DWORD PTR -8[rbp]  ; move eax rbp - 8 (y)
	add	eax, edx                ; add eax to edx
	mov	DWORD PTR -4[rbp], eax  ; move eax to rbp - 4 (z)
	mov	eax, DWORD PTR -8[rbp]  ; move rbp - 8 (y) to eax
	mov	DWORD PTR -12[rbp], eax ; move rbp - 12 (x) eax
	mov	eax, DWORD PTR -4[rbp]  ; move rbp - 4(z) to eax
	mov	DWORD PTR -8[rbp], eax  ; move eax to rbp - 8 (y)
.L2:
	cmp	DWORD PTR -12[rbp], 65534   ; check if rbp - 12 (x) - 0xffff == 0
	jle	.L3                         ; jump if lessthen to L3
	mov	eax, 0                      ; set return value
	leave                           ; same as pop rbp to go back into the previous stack frame
	.cfi_def_cfa 7, 8
	ret                             ; return
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

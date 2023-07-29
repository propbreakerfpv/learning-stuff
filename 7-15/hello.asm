add:
	endbr64
	push	rbp
	mov	rbp, rsp
	mov	DWORD PTR -4[rbp], edi
	mov	DWORD PTR -8[rbp], esi
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	eax, edx
	pop	rbp
	ret
.LC0:
	.string	"hello world"
main:
.LFB1:
	endbr64
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16
	mov	DWORD PTR -12[rbp], 10
	mov	DWORD PTR -8[rbp], 4
	mov	edx, DWORD PTR -8[rbp]
	mov	eax, DWORD PTR -12[rbp]
	mov	esi, edx
	mov	edi, eax
	call	add
	mov	DWORD PTR -4[rbp], eax
	lea	rdi, .LC0[rip]
	call	puts@PLT
	mov	eax, 0
	leave
	ret

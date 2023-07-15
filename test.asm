.section  .rodata
.global test
test:
    .string "hello, world!"

.text
.global main
main:
    jmp exit
exit:
    mov eax, 1  ; syscall number (1 = exit)
    int 0x80    ; call kernel

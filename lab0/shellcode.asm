;shellcode.asm
[SECTION .text]
global _start
_start:
        xor eax, eax
        mov al, 60 
        xor rdi, rdi
        mov rdi, 0xFF
        syscall

# Lab0 - Shellcode Playground

Change whatever is under `_start:` and execute `./assemble.sh` to compile your shellcode.

This is the default shellcode (exit(-1)):

```assembly
;shellcode.asm
[SECTION .text]
global _start
_start:
        xor eax, eax
        mov al, 60 
        xor rdi, rdi
        mov rdi, 0xFF
        syscall

```

You can change it to exit(1) by modifying the shellcode like this:

```assembly
;shellcode.asm
[SECTION .text]
global _start
_start:
        xor eax, eax
        mov al, 60 
        xor rdi, rdi
        mov rdi, 1
        syscall

```
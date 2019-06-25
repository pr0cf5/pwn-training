#!/bin/sh
nasm -f elf64 shellcode.asm
ld -o shellcode shellcode.o


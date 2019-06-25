# Lab2 - Return Oriented Programming

In this lab we are going to practice return-oriented-programming, an ingenious technique devised to bypass ASLR and NX in modern systems.

## makefile
Generally you don't need to interact with this file at all. If for some reason the `attackme` binary does not work on your linux system you may have to make modifications to this file to make it work.

## main.c
Source of the `attackme` binary, the only thing to look for here is the `vuln` function. Look at how the `vuln` function is implemented and what problems it has.

## attackme
The vulnerable binary that you must exploit. Our goal is to obtain a shell by attacking this binary. However, unlike the last lab (return2shellcode) the stack is not executable. You will need to use **ROP** to bypass the unexecutable stack.

## exploit.py
A tiny skeleton code for your exploit. Some important explanations here:

The only things you need to change are:
1. the variable, `payload`: This is the data you will enter into `attackme`. By default it is a large string full of `A`s, but you need to change it appropriately in order to obtain a shell, instead of just crashing the process.

2. the `bp` list in the `debug()` function: Add breakpoints that you wish to inspect closely in the list. 

By now you should know the basic usages of `objdump` and `gdb`.  To set a breakpoint, you must first use `objdump` to disassemble the binary and find the address of the instruction you want to trap into. For example, if one wishes to break at the `ret` instruction of the vuln function, here's what he/she should do:

(1) `objdump -d attackme` => This yields something like this:
```
0000000000401162 <vuln>:
  401162:       55                      push   %rbp
  401163:       48 89 e5                mov    %rsp,%rbp
  401166:       48 83 ec 10             sub    $0x10,%rsp
  40116a:       48 8d 3d 93 0e 00 00    lea    0xe93(%rip),%rdi        # 402004 <_IO_stdin_used+0x4>
  401171:       e8 ba fe ff ff          callq  401030 <puts@plt>
  401176:       48 8d 45 f0             lea    -0x10(%rbp),%rax
  40117a:       48 89 c7                mov    %rax,%rdi
  40117d:       b8 00 00 00 00          mov    $0x0,%eax
  401182:       e8 c9 fe ff ff          callq  401050 <gets@plt>
  401187:       90                      nop
  401188:       c9                      leaveq 
  401189:       c3                      retq 
```

(2) Now since the `retq` instruction is located at 0x401189, we add this number to the bp list, and the `debug` function becomes like this:

```python
def debug():
        script = ""
        bp = [0x401189]
        for x in bp:
                script += "b *0x%x"%x
        gdb.attach(p,gdbscript=script)
```

Uncommenting the debug call and running `exploit.py` will make gdb break at the `retq` instruction of the `vuln` function.

## ROPgadget
You will need to install `ROPgadget`, a tool for finding **gadgets** for ROP. It can be downloaded from the ROPgadget [repo](https://github.com/JonathanSalwan/ROPgadget) or installed via other methods mentioned in the README file of that repo.

The usage is `ROPgadget --binary attackme` and it will display all gadgets. 
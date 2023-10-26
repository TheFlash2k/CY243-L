#!/usr/bin/env python3
import socket
import string
import random
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
port = random.randint(1024, 65535)
s.bind(("0.0.0.0", port))
print(f"[UDP] - Success => {port}. The program is in the running state...")

with open('/port', 'w') as f:
    f.write(str(port))

def generate_flag():
    return f"CY243L_UDP{{{''.join(random.SystemRandom().choice(string.ascii_lowercase + string.digits) for _ in range(32))}}}"

while True:
    data, addr = s.recvfrom(1024)
    print(f"[UDP] - Received buffer: {data}")
    s.sendto(b"Well, you know as the saying goes: Ask, and Ye' shall receive.\n> ", addr)
    try:
        data = data.decode("utf-8")

        if data == "exit":
            s.sendto(b'Well... Bye!', addr)
            break

        if "flag" in data.lower():
            s.sendto(b'Here is your flag:\n' + generate_flag().encode("utf-8") + b"\n> ", addr)
        
    except:
        s.sendto(b"You know, these bytes ain't gon make it work. Try strings\n> ", addr)
        pass
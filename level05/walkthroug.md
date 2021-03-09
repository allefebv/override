# LEVEL 05

## EXPLANATIONS

### BINARY BEHAVIOR
- read stdin and print string uncapitalize
print(buff)  format string exploit
### EXPLOIT STRATEGY

- Overwrite GOT addresses of exit by SHELLCODE (which may be alterate by strtolower())
- GOT of exit : 0x80497e0
### RUN COMMAND

1110011 ^ 0100000 = 1010011
0x20 = 0100000
0x53 = 1010011

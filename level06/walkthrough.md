# LEVEL 06

## EXPLANATIONS

### BINARY BEHAVIOR

- functions : main, auth
- program asks for login and serial
  - login via fgets (32 bytes max) stored in stack buffer.
  - serial via a scanf converted to unsigned int
- sends login buffer and serial nb into auth function

- auth function :
  - replaces \n by \0
  - len of login string must be > 5 + No non printable characters in the string
  - generates a hash value from login string, which is then compared to the serial we provided
    - => if serial provided == hash value => auth returns 0 => call to system("/bin/sh");
  - ptrace with PTRACE_TRACEME is here to prevent we use gdb to retrieve the hash value of login string.

### EXPLOIT STRATEGY

- Input a random string ("aaaaaaa")
- Input a random value for the serial
- Bypass the ptrace
  - break just before it 0x080487ae
  - jump to 0x080487ed inside gdb
- Break at the compare between hash value and serial
  - retrieve hash value for given login string ("aaaaaaa" => 6232801)
  - call the program outside of gdb with same login string and give retrieved hash value as the serial
    - => opens a shell

### RUN COMMAND

```
python -c "print('a' * 7 + '\n' + '6232801')" > /tmp/exploit_string
cat /tmp/exploit_string - | ./level06
```

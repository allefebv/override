# LEVEL 04

## EXPLANATIONS

### BINARY BEHAVIOR

- program asks for a shellcode
- on exit, outputs "exit child"

```
struct user
{
    struct user_regs_struct regs;
    int u_fpvalid;
    struct user_fpregs_struct i387;
    unsigned long int u_tsize;
    unsigned long int u_dsize;
    unsigned long int u_ssize;
    unsigned long int start_code;
    unsigned long int start_stack;
    long int signal;
    int reserved;
    struct user_regs_struct* u_ar0;
    struct user_fpregs_struct* u_fpstate;
    unsigned long int magic;
    char u_comm [32];
    int u_debugreg [8];
};

struct user_regs_struct
{
    long int ebx;
    long int ecx;
    long int edx;
    long int esi;
    long int edi;
    long int ebp;
    long int eax;
    long int xds;
    long int xes;
    long int xfs;
    long int xgs;
    long int orig_eax;
    long int eip;
    long int xcs;
    long int eflags;
    long int esp;
    long int xss;
};
```

- 44 bytes inside the user struct gets us inside the user_regs_struct, precisely to orig_eax.

  - orig_eax is used to save the value inside eax at the moment of a syscall (as eax is then set with the syscall return value).

- /usr/include/bits/waitstatus.h
  - => MACRO WIF
- /usr/include/asm/unistd_32.h

  - => Syscall EXECVE is value 11 (0xb)
  - ptrace

- /usr/include/sys/prctl.h
- /usr/include/bits/signum.h

  - => prctl(1, 1) == prctl(PR_SET_PDEATHSIG, SIGHUP)

- From wait man

  > A state change is considered to be:
  > the child terminated; (returned from its main function)
  > the child was stopped by a signal
  > the child was resumed by a signal.

- ptrace(traceme) / man ptrace / /usr/include/sys/ptrace.h

  - => les appels ultérieurs à execve(2) par ce processus lui enverront (au processus père) SIGTRAP, ce qui donne au père la possibilité de reprendre le contrôle avant que le nouveau programme continue son exécution. Un processus ne doit pas envoyer cette requête si son père n'est pas prêt à le suivre. Dans cette requête, pid, addr et data sont ignorés.

- We understand that if the child process exits normally or with a signal, we will output puts("child is exiting..."); and return.
- If the child does a system interrupt with execve (11) code, the wait will catch it (thanks to ptrace(TRACEME) or exit from main function), output "no exec() for you" and kill the child process.
  - if because of ptrace(TRACEME) sending a SIGTRAP, execve won't even be executed.

### EXPLOIT STRATEGY

- We need to launch the shell other than with a system interrupt execve.

  - => return to libc exploit, we call the system function from C stdlib.

- system from libc is implemented using a fork.

  - Don't know if fork creates a status change, but anyway it won't be a system interrupt with code 11.

- This way we bypass the security

### RUN COMMAND

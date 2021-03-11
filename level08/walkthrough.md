# LEVEL 08

## EXPLANATIONS

### BINARY BEHAVIOR

- functions : main, log_wrapper
- 64bit program
- log_wrapper function :
  - snprintf function that takes argv1 as format string
    - a format string vulnerability, but mitigated by the maximum of 236 bytes max printed.
  - just writes either :
    - Starting back up: + argv1
    - "Finished back up " + argv1
- main function :
  - tries to open path provided with argv1
    - on success, copies content of this file into a backup file (same name, same path, under ./backups/)

### EXPLOIT STRATEGY

- recreate absolute path /home/users/level09/.pass under /tmp/backups/
  - /tmp/backups/home/users/level09/.pass
- provide /home/users/level09/.pass as program argv1

  - execute program from tmp

- program will :
  1. open /home/users/level09/.pass (suid allows it)
  2. store it into /tmp/backups/home/users/level09/.pass

We just have to retrieve its content afterwards

### RUN COMMAND

```
mkdir -p /tmp/backups/home/users/level09/
cd /tmp
~/level08 /home/users/level09/.pass
cat /tmp/backups/home/users/level09/.pass
```

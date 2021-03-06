# LEVEL 00

## EXPLANATIONS

### BINARY BEHAVIOR

- scanf with "%d" format string
  - result is stored at esp+0x1c
- esp+0x1c is then compared to 0x149c
  - if values are equal, branching to system("/bin/sh") is taken

### EXPLOIT STRATEGY

- input the scanf call with value 149c<sub>16</sub> (== 5276<sub>10</sub>)

### RUN COMMAND

```
./level00 5276
```

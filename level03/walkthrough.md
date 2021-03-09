# LEVEL 03

## EXPLANATIONS

### BINARY BEHAVIOR

- inside decrypt function, this string is pushed on the stack
  - => "Q}|u`sfg~sf{}|a3"
- A loop run through this string and modifies it with a xor on string[i] and leet hex - scanf result.
- We saw further in decrypt function that the target string was "Congratulations!"

  - => Searching the xor result outputing a C from a Q, we ended up with value 18<sub>10</sub> (0x12<sub>16</sub> == 0010010<sub>2</sub>)

- 51 => 1010001
- 43 => 1000011

### EXPLOIT STRATEGY

### RUN COMMAND

echo 322424827 | ./level03

# LEVEL 03

## EXPLANATIONS

### BINARY BEHAVIOR

- inside decrypt function, this string is pushed on the stack
  - => "Q}|u`sfg~sf{}|a3"
- A loop run through this string and modifies it with a xor on string[i] and leet hex - scanf result.
- We saw further in decrypt function that the target string was "Congratulations!"

### EXPLOIT STRATEGY

  - => Searching the xor result outputing a C from a Q, we ended up with value 18<sub>10</sub> (0x12<sub>16</sub> == 0010010<sub>2</sub>)

- 'Q' = 0x51 => 1010001
- 'C' = 0x43 => 1000011
-  0x12 => 0010010

0x1337d00d = 322424845  
b = b - a  
b = 322424845 - 18 = 322424827  

### RUN COMMAND
```
***********************************
*		level03		**
***********************************
Password:322424827
```

# LEVEL02

## EXPLANATIONS

### BINARY BEHAVIOR

- printf with format string

### EXPLOIT STRATEGY

- put stack address of "buf_pass" in 1-8th bytes of "buff_password" so that printf will %s on this address
  - => prints content of buff_pass

### RUN COMMAND

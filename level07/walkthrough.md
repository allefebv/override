# LEVEL 07

## EXPLANATIONS

### BINARY BEHAVIOR

- functions : store_number, read_number, main
- program asks for inputs in 3 flavors :

  - store : asks number and index
  - read : asks index and outputs number
  - quit => exits the program

- large number stores int max
  - numbers are considered unsigned int
- large index outputs error

### EXPLOIT STRATEGY

- return to libc with store function.
- write on main sEIP => 0xffffce7c
- start buf store : 0xffffccb4

  - 456 bytes between the two addresses
  - stores at index _ 4 => 114 _ 4 == 456
  - 114 is protected by % 3 protection on provided indexes
  - exploit with unsigned int overflow
    - 4294967295 / 4 == 1073741823
    - 4294967295 % 4 == 3
      - => (1073741823 + 114) \* 4 = 4294967292 + 456 = 4294967748
      - 4294967748 - 4294967295 (== overflow) = 452 (not 453 because 1st value of the overflow is 0)
        - this overflow is insufficient due to remainder of max unsigned division by 4
      - => (1073741823 + 115) \* 4 = 4294967292 + 460 = 4294967752
      - 4294967752 - 4294967295 (== overflow) = 456

- Find addresses of :

  - system
  - exit
  - "/bin/sh"

- overwrite sEIP

### RUN COMMAND

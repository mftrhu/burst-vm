# Burst-vm

**Warning:** this is ~~not complete or useable, even for trivial programs~~ completely broken.

A 16-bit stack-based virtual machine that works with packed instructions. It features 64k of memory and two 256-deep 16-bit stacks, and it comes with a trivial assembler written in Python.

## Instructions format

`1###############`
: Pushes `#` on the data stack.

`0AAAAABBBBBCCCCC`
: Executes the instructions A, B, and C.

### Instructions

|      | Mnemonic | Stack effect   | Other effects     |
| ---- | -------- | -------------- | ----------------- |
| 0x00 | NOP      |                |                   |
| 0x01 | DROP     | a --           |                   |
| 0x02 | SWAP     | a b -- b a     |                   |
| 0x03 | ROT      | a b c -- c a b |                   |
| 0x04 | DUP      | a -- a a       |                   |
| 0x05 | PEEK     | a -- S[a]      |                   |
| 0x06 | ADD      | a b -- a+b     |                   |
| 0x07 | SUB      | a b -- a-b     |                   |
| 0x08 | MUL      | a b -- a*b     |                   |
| 0x09 | DIV      | a b -- a/b     |                   |
| 0x0A | MOD      | a b -- a%b     |                   |
| 0x0B | NEG      | a -- -a        |                   |
| 0x0C | AND      | a b -- a&b     |                   |
| 0x0D | OR       | a b -- a\      |                   |
| 0x0E | XOR      | a b -- a^b     |                   |
| 0x0F | NOT      | a -- ~a        |                   |
| 0x10 | SHR      | a -- a>>1      | Unimplemented     |
| 0x11 | SHL      | a -- a<<1      | Unimplemented     |
| 0x12 | LOAD     | a -- M[a]      |                   |
| 0x13 | STOR     | a b --         | M[b]=a            |
| 0x14 | TOR      | a --           | ( -- a )          |
| 0x15 | RTO      | -- a           | ( a -- )          |
| 0x16 | JUMP     | a --           | PC=a              |
| 0x17 | JZ       | a b --         | PC=b if a==0      |
| 0x18 | CALL     | a --           | ( -- PC), PC=a    |
| 0x19 | RET      |                | ( a -- ), PC=a    |
| 0x1F | HALT     |                | Stops the machine |

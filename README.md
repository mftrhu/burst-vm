# Burst-vm

A 16-bit stack-based virtual machine that works with packed instructions. It features 64k of memory and two 256-deep 16-bit stacks.

## Instructions format

`1###############`
: Pushes `#` on the data stack.

`0AAAAABBBBBCCCCC`
: Executes the instructions A, B, and C.

### Instructions

|      | Mnemonic |
| ---- | -------- |
| 0x00 | NOP      |
| 0x01 | DROP     |
| 0x02 | SWAP     |
| 0x03 | ROT      |
| 0x04 | DUP      |
| 0x05 | PEEK     |
| 0x06 | ADD      |
| 0x07 | SUB      |
| 0x08 | MUL      |
| 0x09 | DIV      |
| 0x0A | MOD      |
| 0x0B | NEG      |
| 0x0C | AND      |
| 0x0D | OR       |
| 0x0E | XOR      |
| 0x0F | NOT      |
| 0x10 | SHR      |
| 0x11 | SHL      |
| 0x12 | LOAD     |
| 0x13 | STOR     |
| 0x14 | LOADB    |
| 0x15 | STORB    |
| 0x16 | JUMP     |
| 0x17 | JZ       |
| 0x18 | CALL     |
| 0x19 | RET      |
| 0x1F | HALT     |

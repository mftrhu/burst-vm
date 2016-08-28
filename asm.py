#!/usr/bin/env python3
"""
asm.py
======

Simple assembler for the burst virtual machine.
"""

test = "main JUMP :sum3 ADD ADD RET :add3 3 ADD RET :main sum3 CALL HALT"

instructions = {
    "ADD": 6,
    "JUMP": 22,
    "JZ": 23,
    "CALL": 24,
    "RET": 25,
    "HALT": 31
}

def assembler(text):
    tokens = text.split()
    position = 0
    labels = {}
    # First pass
    n = 0
    for token in tokens:
        if token.startswith(":"):
            n = 0
            position += 1
            labels[token[1:]] = position
        elif token.isdigit():
            n = 0
            position += 1
        elif token.islower():
            n = 0
            position += 1
        elif token.isupper():
            if n > 3 or token in ("JUMP", "JZ", "CALL", "RET"):
                if n:
                    position += 1
                    n = 0
            n += 1
    # Second pass
    out = []
    instr = 0
    n = 0
    for token in tokens:
        if token.startswith(":"):
            if instr:
                out.append(instr)
                instr = n = 0
        elif token.isdigit():
            if instr:
                out.append(instr)
                instr = n = 0
            out.append(int(token))
        elif token.islower():
            if instr:
                out.append(instr)
                instr = n = 0
            out.append(labels[token])
        elif token.isupper():
            if n > 3 or token in ("JUMP", "JZ", "CALL", "RET"):
                #print(n, token)
                if instr:
                    out.append(instr)
                    instr = n = 0
            instr = instr << 5 | instructions[token]
            n += 1
    if instr:
        out.append(instr)
    print(labels)
    return out

if __name__ == "__main__":
    _ = assembler(test)
    for i, instr in enumerate(_):
        print("%04d: %04X %016s" % (i, instr, bin(instr)[2:]))
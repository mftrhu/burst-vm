#!/usr/bin/env python3
"""
asm.py
======

Simple assembler for the burst virtual machine.
"""
import sys

instructions = {
    "NOP": 0,
    "DROP": 1,
    "SWAP": 2,
    "ROT": 3,
    "DUP": 4,
    "PEEK": 5,
    "ADD": 6,
    "SUB": 7,
    "MUL": 8,
    "DIV": 9,
    "MOD": 10,
    "NEG": 11,
    "AND": 12,
    "OR": 13,
    "XOR": 14,
    "NOT": 15,
    "SHR": 16,
    "SHL": 17,
    "LOAD": 18,
    "STOR": 19,
    "LOADB": 20,
    "STORB": 21,
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
            if n > 3 or token in ("JUMP", "JZ", "CALL", "RET") and not n == 2:
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
            out.append(1 << 15 | int(token))
        elif token.islower():
            if instr:
                out.append(instr)
                instr = n = 0
            out.append(1 << 15 | labels[token])
        elif token.isupper():
            if n > 3 or token in ("JUMP", "JZ", "CALL", "RET") and not n == 2:
                if instr:
                    out.append(instr)
                    instr = n = 0
            instr = instr << 5 | instructions[token]
            n += 1
    if instr:
        out.append(instr)
    print(labels)
    return out

def to_binary(word_stream):
    output = bytearray()
    for word in word_stream:
        output.append((word >> 8) & 0xFF)
        output.append(word & 0xFF)
    return output

#test = "main JUMP :sum3 ADD ADD RET :add3 3 ADD RET :main 1 2 3 sum3 CALL add3 CALL HALT"

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: {0} INFILE OUTFILE".format(sys.argv[0]))
        sys.exit(-1)
    infile = sys.argv[1]
    outfile = sys.argv[2]
    with open(infile, "r") as assembly:
        with open(outfile, "wb") as output:
            output.write(to_binary(assembler(assembly.read(-1))))
            #_ = assembler(test)
    #for i, instr in enumerate(_):
    #    print("%04d: %04X %16s" % (i, instr, bin(instr)[2:]))
    #print(to_binary(_))
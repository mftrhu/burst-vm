#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/* Instructions definitions */
#define NOP 0
#define DROP 1
#define SWAP 2
#define ROT 3
#define DUP 4
#define PEEK 5
#define ADD 6
#define SUB 7
#define MUL 8
#define DIV 9
#define MOD 10
#define NEG 11
#define AND 12
#define OR 13
#define XOR 14
#define NOT 15
#define SHR 16
#define SHL 17
#define LOAD 18
#define STOR 19
#define LOADB 20
#define STORB 21
#define JUMP 22
#define JZ 23
#define CALL 24
#define RET 25
#define HALT 31

/* Constants definition */
#define STACK_SIZE 256
#define MEMORY_SIZE 64 * 1024

bool running = true;
uint8_t memory[MEMORY_SIZE], DP=0, CP=0;
uint16_t PC = 0, IR, data_stack[STACK_SIZE], call_stack[STACK_SIZE];
uint64_t cycles = 0;

void data_push(uint16_t data) {
  data_stack[++DP] = data;
}

uint16_t data_pop() {
  return data_stack[DP--];
}

void call_push(uint16_t data) {
  call_stack[++CP] = data;
}

uint16_t call_pop() {
  return call_stack[CP--];
}

void execute(uint8_t instruction) {
  uint16_t a, b, c;
  switch (instruction) {
    case NOP:
      break;
    case DROP:
      data_pop();
      break;
    case ROT:
      c = data_pop();
      b = data_pop();
      a = data_pop();
      data_push(b);
      data_push(a);
      data_push(c);
      break;
    case DUP:
      a = data_stack[DP];
      data_push(a);
      break;
    case SWAP:
      a = data_pop();
      b = data_pop();
      data_push(a);
      data_push(b);
      break;
    case PEEK:
      a = data_pop();
      if (a > DP) {
        printf("Error: stack underflow.\n");
      } else {
        data_push(data_stack[DP - a]);
      }
      break;
    case ADD:
      b = data_pop();
      a = data_pop();
      data_push(a + b);
      break;
    case SUB:
      b = data_pop();
      a = data_pop();
      data_push(a - b);
      break;
    case MUL:
      b = data_pop();
      a = data_pop();
      data_push(a * b);
      break;
    case DIV:
      b = data_pop();
      a = data_pop();
      data_push(a / b);
      break;
    case MOD:
      b = data_pop();
      a = data_pop();
      data_push(a % b);
      break;
    case NEG:
      a = data_pop();
      data_push(-a);
      break;
    case JUMP:
      PC = data_pop();
      break;
    case JZ:
      a = data_pop();
      b = data_pop();
      if (a == 0) {
        PC = b;
      }
      break;
    case CALL:
      call_push(PC);
      PC = data_pop();
      break;
    case RET:
      PC = call_pop();
      break;
    case HALT:
      running = false;
      break;
    default:
      printf("Error: %X unimplemented.\n", instruction);
  }
  cycles++;
}

void cycle() {
  IR = memory[PC++] << 8 | memory[PC++];
  //printf("PC: %04X IR: %04X\n", PC, IR);
  if (IR >> 15 == 1) {
    //printf("P %04X\n--\n", IR & 0x7fff);
    data_push(IR & 0x7fff);
  } else {
    for (int i = 2; i >= 0; --i) {
      //printf("%02X \n", (IR >> (5 * i)) & 0x1f);
      execute((IR >> (5 * i)) & 0x1f);
    }
  }
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage: %s INFILE\n", argv[0]);
    exit(2);
  } else {
    FILE *fp;
    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
      fprintf(stderr, "Can't open file %s.\n", argv[1]);
      exit(1);
    }
    int c, mp = 0;
    while ((c = fgetc(fp)) != EOF) {
      memory[mp++] = c;
    }
    if (ferror(fp)) {
      fprintf(stderr, "I/O error while reading file.\n");
      exit(1);
    }
    fclose(fp);
  }
  while (running) {
    cycle();
  }
  printf("Cycles: %ld\n", cycles);
  printf("Topstack: %d\n", data_stack[DP]);
  return 0;
}
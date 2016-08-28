#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define STACK_SIZE 256
#define MEMORY_SIZE 64 * 1024

bool running = true;
uint8_t memory[MEMORY_SIZE], DP=0, CP=0;
uint16_t PC = 0, IR, data_stack[STACK_SIZE], call_stack[STACK_SIZE];
uint64_t cycles = 0;

#define NOP 0
#define DROP 1
#define SWAP 2
#define ROT 3
#define DUP 4
#define PEEK 5
#define HALT 31

void data_push(uint16_t data) {
  data_stack[DP++] = data;
}

uint16_t data_pop() {
  return data_stack[DP--];
}

void execute(uint8_t instruction) {
  uint16_t a, b, c;
  switch (instruction) {
    case NOP:
      break;
    case DROP:
      data_pop();
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
  if (IR >> 15 == 1) {
    data_push(IR & 0x7fff);
  } else {
    for (int i = 0; i < 3; ++i) {
      execute((IR >> (5 * i)) & 0x1f);
    }
  }
}

int main(int argc, char const *argv[]) {
  //Debug: Pokes an HALT at the last memory location
  memory[MEMORY_SIZE-1] = 0x001f; 
  while (running) {
    cycle();
  }
  printf("Cycles: %ld\n", cycles);
  return 0;
}
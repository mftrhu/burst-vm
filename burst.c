#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define STACK_SIZE 256
#define MEMORY_SIZE 64 * 1024

bool running = true;
uint8_t memory[MEMORY_SIZE];
uint16_t PC, IR, data_stack[STACK_SIZE], call_stack[STACK_SIZE];



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
  while (running) {
    
  }
  return 0;
}
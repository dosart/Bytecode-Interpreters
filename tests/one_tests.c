#include "one.h"
#include <assert.h>

void test_inc() {
  uint8_t bytecode[] = {OP_INC, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 1);

  printf("test_inc() is done\n");
}

void test_dec() {
  uint8_t bytecode[] = {OP_INC, OP_DEC, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 0);

  printf("test_dec() is done\n");
}

void test_add() {
  uint8_t bytecode[] = {OP_ADDI, 5, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 5);

  printf("test_add() is done\n");
}

void test_add_and_inc() {
  uint8_t bytecode[] = {OP_ADDI, 5, OP_INC, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 6);

  printf("test_add_and_inc() is done\n");
}

void test_add_and_dec() {
  uint8_t bytecode[] = {OP_ADDI, 5, OP_DEC, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 4);

  printf("test_add_and_dec() is done\n");
}

void test_add_and_add() {
  uint8_t bytecode[] = {OP_ADDI, 5, OP_ADDI, 10, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 15);

  printf("test_add_and_add() is done\n");
}

void test_add_and_add_and_dec1() {
  uint8_t bytecode[] = {OP_ADDI, 5, OP_ADDI, 10, OP_DEC, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 14);

  printf("test_add_and_add_and_dec1() is done\n");
}

void test_add_and_add_and_dec2() {
  uint8_t bytecode[] = {OP_INC, OP_ADDI, 5, OP_ADDI, 10, OP_DEC, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 15);

  printf("test_add_and_add_and_dec2() is done\n");
}

void test_error() {
  uint8_t bytecode[] = {OP_INC, OP_ADDI, 5, OP_ADDI, 10, OP_DEC, 232, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.result == ERROR_UNKNOWN_OPCODE);

  printf("test_error() is done\n");
}

void run_all_tests() {
  test_inc();
  test_dec();
  test_add();
  test_add_and_inc();
  test_add_and_dec();
  test_add_and_add();
  test_add_and_add_and_dec1();
  test_add_and_add_and_dec2();
  test_error();
}

int main() { run_all_tests(); }
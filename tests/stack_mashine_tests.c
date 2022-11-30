#include "stack_machine.h"
#include <assert.h>

void test_done() {
  uint8_t bytecode[] = {OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.result == DONE);

  printf("test_done() is done\n");
}

void test_push_value() {
  uint8_t bytecode[] = {OP_PUSHI, 10, OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 10);

  printf("test_push_value() is done\n");
}

void test_add() {
  uint8_t bytecode[] = {OP_PUSHI, 10,         OP_PUSHI, 10,
                        OP_ADD,   OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 20);

  printf("test_add() is done\n");
}

void test_mul() {
  uint8_t bytecode[] = {OP_PUSHI, 10,         OP_PUSHI, 10,
                        OP_MUL,   OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 100);

  printf("test_mul() is done\n");
}

void test_div1() {
  uint8_t bytecode[] = {OP_PUSHI, 10, OP_PUSHI, 1, OP_DIV, OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 10);
  assert(r.result == DONE);

  printf("test_div1() is done\n");
}

void test_div2() {
  uint8_t bytecode[] = {OP_PUSHI, 10, OP_PUSHI, 0, OP_DIV, OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.result == ERROR_DIVISION_BY_ZERO);

  printf("test_div2() is done\n");
}

void test_add_and_add() {
  uint8_t bytecode[] = {OP_PUSHI, 10, OP_PUSHI, 10,         OP_ADD,
                        OP_PUSHI, 10, OP_ADD,   OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 30);

  printf("test_add_and_add() is done\n");
}

void test_add_and_sub() {
  uint8_t bytecode[] = {OP_PUSHI, 10, OP_PUSHI, 10,         OP_ADD,
                        OP_PUSHI, 10, OP_SUB,   OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 10);

  printf("test_add_and_sub() is done\n");
}

void test_add_and_mull() {
  uint8_t bytecode[] = {OP_PUSHI, 10, OP_PUSHI, 10,         OP_ADD,
                        OP_PUSHI, 5,  OP_MUL,   OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 100);

  printf("test_add_and_mull() is done\n");
}

void test_sub_and_mull() {
  uint8_t bytecode[] = {OP_PUSHI, 100, OP_PUSHI, 10,         OP_SUB,
                        OP_PUSHI, 5,   OP_MUL,   OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 450);

  printf("test_sub_and_mull() is done\n");
}

void test_sub_and_mull_and_div() {
  uint8_t bytecode[] = {OP_PUSHI, 10,         OP_PUSHI, 10,       OP_ADD,
                        OP_PUSHI, 5,          OP_MUL,   OP_PUSHI, 100,
                        OP_DIV,   OP_POP_RES, OP_DONE};
  result_t r = vm_run(bytecode);

  assert(r.accumulator == 1);

  printf("test_sub_and_mull_and_div() is done\n");
}

void run_all_test() {
  test_done();
  test_push_value();
  test_add();
  test_mul();
  test_div1();
  test_div2();
  test_add_and_add();
  test_add_and_sub();
  test_add_and_mull();
  test_sub_and_mull();
  test_sub_and_mull_and_div();
}

int main() { run_all_test(); }
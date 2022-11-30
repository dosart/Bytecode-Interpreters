#ifndef STACK_MASHINE_H
#define STACK_MASHINE_H

#include <stdint.h>
#include <stdio.h>

#define STACK_MAX 256

typedef struct __vm_t {
  uint8_t *ip;

  /* Fixed-size stack */
  uint64_t stack[STACK_MAX];
  uint64_t *stack_top;

  /* A single register containing the result */
  uint64_t result;
} vm_t;

typedef enum {
  /* push the immediate argument onto the stack */
  OP_PUSHI,
  /* pop 2 values from the stack, add and push the result onto the stack */
  OP_ADD,
  /* pop 2 values from the stack, subtract and push the result onto the stack */
  OP_SUB,
  /* pop 2 values from the stack, divide and push the result onto the stack */
  OP_DIV,
  /* pop 2 values from the stack, multiply and push the result onto the stack */
  OP_MUL,
  /* pop the top of the stack and set it as execution result */
  OP_POP_RES,
  /* stop execution */
  OP_DONE,
} opcode_t;

typedef enum __interpret_result_t {
  SUCCESS = 1,
  DONE,
  ERROR_DIVISION_BY_ZERO,
  ERROR_UNKNOWN_OPCODE,
} interpret_result_t;

typedef struct __result_t {
  interpret_result_t result;
  uint64_t accumulator;
} result_t;

void vm_init(vm_t *vm, uint8_t *bytecode);

void vm_stack_push(vm_t *vm, uint64_t value);

uint64_t vm_stack_pop(vm_t *vm);

interpret_result_t vm_decode_and_execute(vm_t *vm, uint8_t instruction);

result_t vm_run(uint8_t *bytecode);

#endif
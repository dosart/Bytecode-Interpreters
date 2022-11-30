#ifndef ONE_MASHINE_H
#define ONE_MASHINE_H

#include <stdint.h>
#include <stdio.h>

typedef struct __vm_t {
  uint8_t *ip;
  uint64_t accumulator;
} vm_t;

typedef enum __opcode_t {
  /* increment the register */
  OP_INC,
  /* decrement the register */
  OP_DEC,
  /* add the immediate argument to the register */
  OP_ADDI,
  /* subtract the immediate argument from the register */
  OP_SUBI,
  /* stop execution */
  OP_DONE
} opcode_t;

typedef enum __interpret_result_t {
  SUCCESS = 1,
  DONE,
  ERROR_UNKNOWN_OPCODE,
} interpret_result_t;

typedef struct __result_t {
  interpret_result_t result;
  uint64_t accumulator;
} result_t;

uint8_t vm_fetch(vm_t *vm);

interpret_result_t vm_decode_and_execute(vm_t *vm, uint8_t instruction);

result_t vm_run(uint8_t *bytecode);

#endif
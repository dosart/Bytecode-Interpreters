#ifndef REGISTER_MASHINE_H
#define REGISTER_MASHINE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTER_NUM 16

typedef struct __vm_t {
  uint16_t *ip;

  /* Register array */
  uint64_t reg[REGISTER_NUM];

  /* A single register containing the result */
  uint64_t result;
} vm_t;

typedef enum {
  /* Load an immediate value into r0  */
  OP_LOADI,
  /* Add values in r0,r1 registers and put them into r2 */
  OP_ADD,
  /* Subtract values in r0,r1 registers and put them into r2 */
  OP_SUB,
  /* Divide values in r0,r1 registers and put them into r2 */
  OP_DIV,
  /* Multiply values in r0,r1 registers and put them into r2 */
  OP_MUL,
  /* Move a value from r0 register into the result register */
  OP_MOV_RES,
  /* stop execution */
  OP_DONE,
} opcode_t;

typedef enum __interpret_result_t {
  SUCCESS = 1,
  DONE,
  ERROR_DIVISION_BY_ZERO,
  ERROR_UNKNOWN_OPCODE,
} interpret_result_t;

#endif
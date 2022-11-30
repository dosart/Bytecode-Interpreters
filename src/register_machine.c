#include "register_machine.h"

void vm_init(vm_t *vm, uint16_t *bytecode) {
  if (vm == NULL)
    return;
  vm->ip = bytecode;
  memset(vm->reg, 0, sizeof(uint64_t) * REGISTER_NUM);
}

uint16_t vm_fetch(vm_t *vm) { return *vm->ip++; }

void vm_decode(uint16_t instruction, uint8_t *op, uint8_t *reg0, uint8_t *reg1,
               uint8_t *reg2, uint8_t *imm) {
  *op = (instruction & 0xF000) >> 12;
  *reg0 = (instruction & 0x0F00) >> 8;
  *reg1 = (instruction & 0x00F0) >> 4;
  *reg2 = (instruction & 0x000F);
  *imm = (instruction & 0x00FF);
}

interpret_result_t vm_decode_and_execute(vm_t *vm, uint16_t instruction) {

  uint8_t op, r0, r1, r2, immediate;
  decode(instruction, &op, &r0, &r1, &r2, &immediate);
  switch (op) {
  case OP_LOADI: {
    vm->reg[r0] = immediate;
    return SUCCESS;
  }
  case OP_ADD: {
    vm->reg[r2] = vm->reg[r0] + vm->reg[r1];
    return SUCCESS;
  }
  case OP_SUB: {
    vm->reg[r2] = vm->reg[r0] - vm->reg[r1];
    return SUCCESS;
  }
  case OP_DIV: {
    if (vm->reg[r1] == 0)
      return ERROR_DIVISION_BY_ZERO;
    vm->reg[r2] = vm->reg[r0] / vm->reg[r1];
    return SUCCESS;
  }
  case OP_MUL: {
    vm->reg[r2] = vm->reg[r0] * vm->reg[r1];
    return SUCCESS;
  }
  case OP_MOV_RES: {
    vm->result = vm->reg[r0];
    return SUCCESS;
  }
  case OP_DONE: {
    return DONE;
  }
  default:
    return ERROR_UNKNOWN_OPCODE;
  }

  return SUCCESS;
}
#include "one.h"

void vm_init(vm_t *vm, uint8_t *bytecode) {
  if (vm == NULL)
    return;
  vm->ip = bytecode;
  vm->accumulator = 0;
}

uint8_t vm_fetch(vm_t *vm) { return *vm->ip++; }

interpret_result_t vm_decode_and_execute(vm_t *vm, uint8_t instruction) {
  switch (instruction) {
  case OP_INC: {
    vm->accumulator++;
    return SUCCESS;
  }
  case OP_DEC: {
    vm->accumulator--;
    return SUCCESS;
  }
  case OP_ADDI: {
    /* get the argument */
    uint8_t arg = *vm->ip++;
    vm->accumulator += arg;
    return SUCCESS;
  }
  case OP_SUBI: {
    /* get the argument */
    uint8_t arg = *vm->ip++;
    vm->accumulator -= arg;
    return SUCCESS;
  }
  case OP_DONE: {
    return DONE;
  }
  default:
    return ERROR_UNKNOWN_OPCODE;
  }
}

result_t vm_run(uint8_t *bytecode) {
  vm_t vm;
  vm_init(&vm, bytecode);

  uint8_t instruction;
  interpret_result_t result;
  for (;;) {
    instruction = vm_fetch(&vm);
    result = vm_decode_and_execute(&vm, instruction);

    if (result == SUCCESS)
      continue;
    else
      break;
  }

  result_t r;
  r.result = result;
  r.accumulator = vm.accumulator;

  return r;
}

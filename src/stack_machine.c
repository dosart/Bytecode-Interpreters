#include "stack_machine.h"

void vm_init(vm_t *vm, uint8_t *bytecode) {
  if (vm == NULL)
    return;
  vm->ip = bytecode;
  vm->stack_top = vm->stack;
}

void vm_stack_push(vm_t *vm, uint64_t value) {
  *vm->stack_top = value;
  vm->stack_top++;
}

uint64_t vm_stack_pop(vm_t *vm) {
  vm->stack_top--;
  return *vm->stack_top;
}

uint8_t vm_fetch(vm_t *vm) { return *vm->ip++; }

interpret_result_t vm_decode_and_execute(vm_t *vm, uint8_t instruction) {
  switch (instruction) {
  case OP_PUSHI: {
    /* get the argument, push it onto stack */
    uint8_t arg = *vm->ip++;
    vm_stack_push(vm, arg);
    return SUCCESS;
  }
  case OP_ADD: {
    /* Pop 2 values, add 'em, push the result back to the stack */
    uint64_t arg_right = vm_stack_pop(vm);
    uint64_t arg_left = vm_stack_pop(vm);
    uint64_t res = arg_left + arg_right;
    vm_stack_push(vm, res);
    return SUCCESS;
  }
  case OP_SUB: {
    /* Pop 2 values, subtract 'em, push the result back to the stack */
    uint64_t arg_right = vm_stack_pop(vm);
    uint64_t arg_left = vm_stack_pop(vm);
    uint64_t res = arg_left - arg_right;
    vm_stack_push(vm, res);
    return SUCCESS;
  }
  case OP_DIV: {
    /* Pop 2 values, divide 'em, push the result back to the stack */
    uint64_t arg_right = vm_stack_pop(vm);
    /* Don't forget to handle the div by zero error */
    if (arg_right == 0)
      return ERROR_DIVISION_BY_ZERO;
    uint64_t arg_left = vm_stack_pop(vm);
    uint64_t res = arg_left / arg_right;
    vm_stack_push(vm, res);
    return SUCCESS;
  }
  case OP_MUL: {
    /* Pop 2 values, multiply 'em, push the result back to the stack */
    uint64_t arg_right = vm_stack_pop(vm);
    uint64_t arg_left = vm_stack_pop(vm);
    uint64_t res = arg_left * arg_right;
    vm_stack_push(vm, res);
    return SUCCESS;
  }
  case OP_POP_RES: {
    /* Pop the top of the stack, set it as a result value */
    uint64_t res = vm_stack_pop(vm);
    vm->result = res;
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
  r.accumulator = vm.result;

  return r;
}
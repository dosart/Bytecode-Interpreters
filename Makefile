CC:=gcc
CC_FLAGS:=-I ./include -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion
OUTPUT_DIR:=./build
STACK_MACHINE_TESTS:=stack_machine_tests
ONE_TESTS:=one_tests

.PHONY: make_format create_output_dir run_all_tests clean memcheck

make_format:
	./make_format.sh

create_output_dir:
	mkdir -p $(OUTPUT_DIR)

make_one_tests : make_format create_output_dir include/one.h
	$(CC) $(CC_FLAGS) src/one.c tests/one_tests.c -o $(OUTPUT_DIR)/$(ONE_TESTS)

run_one_tests: make_format make_one_tests
	./$(OUTPUT_DIR)/$(ONE_TESTS)

make_stack_machine_tests : create_output_dir include/stack_machine.h
	$(CC) $(CC_FLAGS) src/stack_machine.c tests/stack_mashine_tests.c -o $(OUTPUT_DIR)/$(STACK_MACHINE_TESTS)

run_stack_machine_tests: make_stack_machine_tests
	./$(OUTPUT_DIR)/$(STACK_MACHINE_TESTS)

run_all_tests: run_one_tests run_stack_machine_tests

clean:
	rm $(OUTPUT_DIR)/*

memcheck: run_stack_machine_tests run_one_tests
	valgrind --leak-check=yes --track-origins=yes -s ./$(OUTPUT_DIR)/$(STACK_MACHINE_TESTS)
	valgrind --leak-check=yes --track-origins=yes -s ./$(OUTPUT_DIR)/$(ONE_TESTS)

#ifndef HAL_PROCESSOR_FAULTS_TEST_H
#define HAL_PROCESSOR_FAULTS_TEST_H


void generate_undefined_instruction_usagefault(void);
void generate_invalid_state_usagefault(void);
void generate_divide_by_zero_usagefault(void);

#endif // HAL_PROCESSOR_FAULTS_TEST_H
#include <stdbool.h>
#include <stdlib.h>

#include "minilibmx.h"

int mx_length_of_input_type_array(enum e_input_type *input_type_array) {
    int len = 0;

    while(input_type_array != 0) {
        len++;
        input_type_array++;
    }

    return len;
}

bool is_unknown_variable(const char *str) {
    while (*str != '\0') {
        if (*str == '?') {
            return true;
        }
        str++;
    }

    return false;
}

enum e_input_type *mx_find_unknown_variables(const char *operand1,
                                             const char *operation,
                                             const char *operand2,
                                             const char *result,
                                             int *array_length) {
    bool operand1_is_unknown = is_unknown_variable(operand1);
    bool operand2_is_unknown = is_unknown_variable(operand2);
    bool operation_is_unknown = is_unknown_variable(operation);
    bool result_is_unknown = is_unknown_variable(result);
    
    int count_of_unknown_variables = (int)operand1_is_unknown
                                     + (int)operand2_is_unknown
                                     + (int)operation_is_unknown
                                     + (int)result_is_unknown;
    
    enum e_input_type *unknown_variables = (enum e_input_type*)malloc(sizeof(enum e_input_type) * (count_of_unknown_variables));

    int index = 0;
    if (operand1_is_unknown) {
        unknown_variables[index++] = OPERAND1;
    }
    if (operand2_is_unknown) {
        unknown_variables[index++] = OPERAND2;
    }
    if (operation_is_unknown) {
        unknown_variables[index++] = OPERATION;
    }
    if (result_is_unknown) {
        unknown_variables[index++] = RESULT;
    }

    *array_length = index;

    return unknown_variables;
}


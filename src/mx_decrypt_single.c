#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "minilibmx.h"

enum e_operation *find_unknown_operations(int operand1,
                                         int operand2, 
                                         int equal,
                                         int *array_size) {
    int operations_count = 0;

    if (operand1 + operand2 == equal) {
        operations_count++;
    }
    if (operand1 - operand2 == equal) {
        operations_count++;
    }
    if (operand1 * operand2 == equal) {
        operations_count++;
    }
    if (operand2 != 0 && operand1 / operand2 == equal) {
        operations_count++;
    }

    enum e_operation *operations_array = (enum e_operation*)malloc(sizeof(enum e_operation) * operations_count);
    int index = 0;

    if (operand1 + operand2 == equal) {
        operations_array[index++] = ADD;
    }
    if (operand1 - operand2 == equal) {
        operations_array[index++] = SUB;
    }
    if (operand1 * operand2 == equal) {
        operations_array[index++] = MUL;
    }
    if (operand2 != 0 && operand1 / operand2 == equal) {
        operations_array[index++] = DIV;
    }

    *array_size = index;

    return operations_array;
}

const char *operation_enum_to_str(enum e_operation op) {
    switch(op) {
        case ADD:
            return "+";
        case SUB:
            return "-";
        case MUL:
            return "*";
        case DIV:
            return "/";
        default:
            return "\0"; 
    }
}

enum e_operation get_operation_enum(const char *op) {
    switch(*op) {
        case '-':
            return SUB;
        case '+':
            return ADD;
        case '*':
            return MUL;
        case '/':
            return DIV;
        default:
            return UNKNOWN; 
    }
}


char *format_expression(const char *operand1,
                        const char *operand2,
                        const char *operation,
                        const char *result) {
    char *operand1_trimmed = mx_decimal_to_string(mx_atoi(operand1));
    char *operand2_trimmed = mx_decimal_to_string(mx_atoi(operand2));
    char *result_trimmed = mx_decimal_to_string(mx_atoi(result));


    char *variables_array[6] = {operand1_trimmed,
                                (char*)operation,
                                operand2_trimmed, "=",
                                result_trimmed, NULL};

    char *expression_str = mx_concat_words(variables_array);

    free(operand1_trimmed);
    free(operand2_trimmed);
    free(result_trimmed);

    return expression_str;
}

// assumes that there is no division by zero
char **create_array_of_valid_expressions_for_operand1(const char *operand1,
                                                      enum e_operation operation_enum,
                                                      const char *operation,
                                                      int operand2_int,
                                                      const char *operand2,
                                                      int result_int,
                                                      const char *result,
                                                      int unknown_variable_max,
                                                      int unknown_variable_min) {
    if (operation_enum == ADD
        || operation_enum == SUB
        || (operation_enum == MUL && operand2_int != 0 && result_int != 0)) {
        int operand1_value = mx_solve_equation(0, operand2_int, operation_enum, result_int, OPERAND1);

        if (mx_perform_operation(operation_enum, operand1_value, operand2_int) == result_int
            && mx_is_fits_template(operand1_value, operand1)) {
            char **array_of_valid_expressions = (char**)malloc(sizeof(char*) * 2);
            char *operand1_str = mx_decimal_to_string(operand1_value);
            
            array_of_valid_expressions[0] = format_expression(
                operand1_str,
                operand2,
                operation,
                result
            );

            free(operand1_str);

            array_of_valid_expressions[1] = NULL;

            return array_of_valid_expressions;
        }

        return NULL;
    }

    int count_of_vaild_expresions = 0;

    // does not work when number_max = 2147483647
    for (int num = unknown_variable_min; num <= unknown_variable_max; mx_get_next_step(&num, operand1, unknown_variable_max)) {
        if (mx_perform_operation(operation_enum, num, operand2_int) == result_int) {
            count_of_vaild_expresions++;
        }

        if (num == INT_MAX) {
            break;
        }
    }

    char **unknown_variables_value_array = (char**)malloc(sizeof(char*) * (count_of_vaild_expresions + 1));
    int unknown_variables_value_array_index = 0;

    for (int num = unknown_variable_min; num <= unknown_variable_max; mx_get_next_step(&num, operand1, unknown_variable_max)) {
        if (mx_perform_operation(operation_enum, num, operand2_int) == result_int) {
            char *num_str = mx_decimal_to_string(num);

            unknown_variables_value_array[unknown_variables_value_array_index++] = format_expression(
                num_str,
                operand2,
                operation,
                result
            );

            free(num_str);
        }

        if (num == INT_MAX) {
            break;
        }
    }

    unknown_variables_value_array[unknown_variables_value_array_index] = NULL;

    return unknown_variables_value_array;
}

char **create_array_of_valid_expressions_for_operand2(const char *operand1,
                                                      int operand1_int,
                                                      enum e_operation operation_enum,
                                                      const char *operation,
                                                      const char *operand2,
                                                      int result_int,
                                                      const char *result,
                                                      int unknown_variable_max,
                                                      int unknown_variable_min) {
    if (operation_enum == ADD
        || operation_enum == SUB
        || (operation_enum == MUL && operand1_int != 0 && result_int != 0)) {
        int operand2_value = mx_solve_equation(operand1_int, 0, operation_enum, result_int, OPERAND2);

        if (mx_perform_operation(operation_enum, operand1_int, operand2_value) == result_int
            && mx_is_fits_template(operand2_value, operand2)) {
            char **array_of_valid_expressions = (char**)malloc(sizeof(char*) * 2);
            char *operand2_str = mx_decimal_to_string(operand2_value);
            
            array_of_valid_expressions[0] = format_expression(
                operand1,
                operand2_str,
                operation,
                result
            );

            free(operand2_str);

            array_of_valid_expressions[1] = NULL;

            return array_of_valid_expressions;
        }

        return NULL;
    }

    int count_of_vaild_expresions = 0;

    // does not work when number_max = 2147483647
    for (int num = unknown_variable_min; num <= unknown_variable_max; mx_get_next_step(&num, operand2, unknown_variable_max)) {
        if (!(num == 0 && operation_enum == DIV)
            && mx_perform_operation(operation_enum, operand1_int, num) == result_int) {
            count_of_vaild_expresions++;
        }

        if (num == INT_MAX) {
            break;
        }
    }

    char **unknown_variables_value_array = (char**)malloc(sizeof(char*) * (count_of_vaild_expresions + 1));
    int unknown_variables_value_array_index = 0;

    for (int num = unknown_variable_min; num <= unknown_variable_max; mx_get_next_step(&num, operand2, unknown_variable_max)) {
        if (!(num == 0 && operation_enum == DIV)
            && mx_perform_operation(operation_enum, operand1_int, num) == result_int) {
            char *num_str = mx_decimal_to_string(num);

            unknown_variables_value_array[unknown_variables_value_array_index++] = format_expression(
                operand1,
                num_str,
                operation,
                result
            );

            free(num_str);
        }

        if (num == INT_MAX) {
            break;
        }
    }

    unknown_variables_value_array[unknown_variables_value_array_index] = NULL;

    return unknown_variables_value_array;
}

char **create_array_of_valid_expressions_for_operation(int operand1_int, const char *operand1,
                                                       int operand2_int, const char *operand2,
                                                       int result_int, const char *result) {
    int count_of_valid_expresions;

    enum e_operation *valid_operations = find_unknown_operations(
        operand1_int,
        operand2_int,
        result_int,
        &count_of_valid_expresions
    );

    if (count_of_valid_expresions == 0) {
        return NULL;
    }

    char **array_of_valid_expressions = (char**)malloc(sizeof(char*) * (count_of_valid_expresions + 1));

    for (int i = 0; i < count_of_valid_expresions; i++) {
        const char *operation_str = operation_enum_to_str(valid_operations[i]);
        
        array_of_valid_expressions[i] = format_expression(
            operand1,
            operand2,
            operation_str,
            result
        );
    }

    array_of_valid_expressions[count_of_valid_expresions] = NULL;

    return array_of_valid_expressions;
}

char **create_array_of_valid_expressions_for_result(const char *operand1, int operand1_int,
                                                    enum e_operation operation_enum, const char *operation,
                                                    const char *operand2, int operand2_int,
                                                    const char *result) {
    int result_value = mx_perform_operation(operation_enum, operand1_int, operand2_int);
    
    if (mx_is_fits_template(result_value, result)) {
        char **array_of_valid_expressions = (char**)malloc(sizeof(char*) * 2);
        char *result_str = mx_decimal_to_string(result_value);
            
        array_of_valid_expressions[0] = format_expression(
            operand1,
            operand2,
            operation,
            result_str
        );

        free(result_str);

        array_of_valid_expressions[1] = NULL;

        return array_of_valid_expressions;
    }

    return NULL;
}

// assumes that input values are all valid and
// that there is only one unknown variable
char **mx_decrypt_single(const char *operand1,
                         const char *operation,
                         const char *operand2,
                         const char *result,
                         enum e_input_type unknown_variable_enum) {
    int operand1_int;
    int operand2_int;
    enum e_operation operation_enum;
    int result_int;
    char **array_of_valid_expressions;

    switch (unknown_variable_enum) {
        case OPERAND1:
            operand1_int = 0;
            operand2_int = mx_atoi(operand2);
            operation_enum = get_operation_enum(operation);
            result_int = mx_atoi(result);

            if (operation_enum == DIV && operand2_int == 0) {
                return NULL;
            }

            int operand1_max;
            int operand1_min;
            
            mx_find_inclusive_limits(operand1, &operand1_max, &operand1_min);

            array_of_valid_expressions = create_array_of_valid_expressions_for_operand1(
                operand1,
                operation_enum, operation,
                operand2_int, operand2,
                result_int, result,
                operand1_max, operand1_min
            );

            return array_of_valid_expressions;
            
        case OPERAND2:
            operand1_int = mx_atoi(operand1);
            operand2_int = 0;
            operation_enum = get_operation_enum(operation);
            result_int = mx_atoi(result);

            int operand2_max;
            int operand2_min;

            mx_find_inclusive_limits(operand2, &operand2_max, &operand2_min);

            array_of_valid_expressions = create_array_of_valid_expressions_for_operand2(
                operand1, operand1_int,
                operation_enum, operation,
                operand2,
                result_int, result,
                operand2_max, operand2_min
            );

            return array_of_valid_expressions;
        case OPERATION:
            operand1_int = mx_atoi(operand1);
            operand2_int = mx_atoi(operand2);
            operation_enum = UNKNOWN;
            result_int = mx_atoi(result);

            array_of_valid_expressions = create_array_of_valid_expressions_for_operation(
                operand1_int, operand1,
                operand2_int, operand2,
                result_int, result
            );

            return array_of_valid_expressions;
        case RESULT:
            operand1_int = mx_atoi(operand1);
            operand2_int = mx_atoi(operand2);
            operation_enum = get_operation_enum(operation);
            result_int = 0;

            if (operand2_int == 0 && operation_enum == DIV) {
                return NULL;
            }

            array_of_valid_expressions = create_array_of_valid_expressions_for_result(
                operand1, operand1_int,
                operation_enum, operation,
                operand2, operand2_int,
                result
            );

            return array_of_valid_expressions;

        default:
            return NULL;
    }
}


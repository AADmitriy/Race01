#include <stdbool.h>
#include <stdlib.h>

#include "minilibmx.h"

bool is_in_array(enum e_input_type input_type,
                 enum e_input_type *input_type_array,
                 int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (input_type_array[i] == input_type) {
            return true;
        }
    }

    return false;
}

char **mx_decrypt_all(const char *operand1,
                   const char *operation,
                   const char *operand2,
                   const char *result,
                   enum e_input_type *unknown_variable_enums,
                   int unknown_variables_count) {

    if (unknown_variables_count == 1) {
        char **array_of_valid_expressions = mx_decrypt_single(
            operand1,
            operation,
            operand2,
            result,
            unknown_variable_enums[0]
        );

        return array_of_valid_expressions;
    }
    else {
        if (is_in_array(OPERATION, unknown_variable_enums, unknown_variables_count)) {
            const char *operations_array[4] = {"+", "-", "*", "/"};
            enum e_input_type *subbed_array = mx_input_type_array_sub(
                OPERATION,
                unknown_variable_enums,
                unknown_variables_count
            );

            char **valid_expresions = NULL;
            for (int i = 0; i < 4; i++) {
                char **new_array = mx_decrypt_all(
                    operand1,
                    operations_array[i],
                    operand2,
                    result,
                    subbed_array,
                    unknown_variables_count - 1
                );

                valid_expresions = mx_join_string_arrays(valid_expresions, new_array);
            }

            free(subbed_array);

            return valid_expresions;
        }
        else if (is_in_array(OPERAND1, unknown_variable_enums, unknown_variables_count)){
            enum e_input_type *subbed_array = mx_input_type_array_sub(
                OPERAND1,
                unknown_variable_enums,
                unknown_variables_count
            );

            int operand1_max;
            int operand1_min;
            
            mx_find_inclusive_limits(operand1, &operand1_max, &operand1_min);

            char **valid_expresions = NULL;
            for (int operand1_int = operand1_min; operand1_int <= operand1_max; mx_get_next_step(&operand1_int, operand1, operand1_max)) {
                char *operand1_str = mx_decimal_to_string(operand1_int);

                char **new_array = mx_decrypt_all(
                    operand1_str,
                    operation,
                    operand2,
                    result,
                    subbed_array,
                    unknown_variables_count - 1
                );

                valid_expresions = mx_join_string_arrays(valid_expresions, new_array);

                free(operand1_str);
            }

            free(subbed_array);

            return valid_expresions;
        }
        else if (is_in_array(OPERAND2, unknown_variable_enums, unknown_variables_count)) {
            enum e_input_type *subbed_array = mx_input_type_array_sub(
                OPERAND2,
                unknown_variable_enums,
                unknown_variables_count
            );

            int operand2_max;
            int operand2_min;
            
            mx_find_inclusive_limits(operand2, &operand2_max, &operand2_min);

            char **valid_expresions = NULL;
            for (int operand2_int = operand2_min; operand2_int <= operand2_max; mx_get_next_step(&operand2_int, operand2, operand2_max)) {
                char *operand2_str = mx_decimal_to_string(operand2_int);

                char **new_array = mx_decrypt_all(
                    operand1,
                    operation,
                    operand2_str,
                    result,
                    subbed_array,
                    unknown_variables_count - 1
                );

                valid_expresions = mx_join_string_arrays(valid_expresions, new_array);

                free(operand2_str);
            }

            free(subbed_array);

            return valid_expresions;
        }
        else {
            return NULL;
        }
    }
}


#include <stdlib.h>
#include <stdio.h>

#include "minilibmx.h"

bool is_valid_num(const char *str) {
    while (mx_isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        str++;
    }
    else if (*str == '+') {
        str++;
    }

    while (mx_isdigit(*str) || *str == '?') {    
        str++;
    }
    
    while (mx_isspace(*str)) {
        str++;
    }
    
    if (*str != '\0') {
        return false;
    }
    
    return true;
}

bool is_valid_operation(const char *op) {
    char *operation = mx_strtrim(op);

    if (mx_strlen(operation) != 1) {
        return false;
    }

    char op_char = operation[0];

    mx_strdel(&operation);

    return op_char == '+'
           || op_char == '-'
           || op_char == '*'
           || op_char == '/'
           || op_char == '?';
}

void print_array_of_str(char **str) {
    if (str == NULL) {
        return;
    }

    for (int i = 0; str[i] != NULL; i++) {
        mx_printstr(str[i]);
        mx_printchar('\n');
    }
}

void free_array_of_str(char ***str_ptr) {
    if (str_ptr == NULL || *str_ptr == NULL) {
        return;
    }

    char **str_array = *str_ptr;
    for (int i = 0; str_array[i] != NULL; i++) {
        free(str_array[i]);
    }

    free(str_array);
    *str_ptr = NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        mx_printerr("usage: ./part_of_the_matrix [operand1] [operation] [operand2] [result]\n");
        exit(EXIT_FAILURE);
    }

    if (!is_valid_operation(argv[2])) {
        mx_printerr("Invalid operation: ");
        mx_printerr(argv[2]);
        mx_printerr("\n");
        exit(INCORRECT_OPERATION);
    }

    if (!is_valid_num(argv[1])) {
        mx_printerr("Invalid operand: ");
        mx_printerr(argv[1]);
        mx_printerr("\n");
        exit(INCORRECT_OPERAND);
    }
    
    if (!is_valid_num(argv[3])) {
        mx_printerr("Invalid operand: ");
        mx_printerr(argv[3]);
        mx_printerr("\n");
        exit(INCORRECT_OPERAND);
    }

    if (!is_valid_num(argv[4])) {
        mx_printerr("Invalid result: ");
        mx_printerr(argv[4]);
        mx_printerr("\n");
        exit(INCORRECT_OPERAND);
    }

    char *operand1 = mx_strtrim(argv[1]);
    char *operation = mx_strtrim(argv[2]);
    char *operand2 = mx_strtrim(argv[3]);
    char *result = mx_strtrim(argv[4]);
    
    int input_type_array_length;
    enum e_input_type *input_type_array = mx_find_unknown_variables(
        operand1,
        operation,
        operand2,
        result,
        &input_type_array_length
    );

    char **valid_expressions = mx_decrypt_all(
        operand1,
        operation,
        operand2,
        result,
        input_type_array,
        input_type_array_length
    );
    
    print_array_of_str(valid_expressions);

    free_array_of_str(&valid_expressions);

    free(operand1);
    free(operation);
    free(operand2);
    free(result);
    free(input_type_array);

    exit(EXIT_SUCCESS);
}


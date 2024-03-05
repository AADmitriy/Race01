#pragma once
#include <stdbool.h>
#include <stdio.h>

enum e_operation {
    ADD,
    SUB,
    MUL,
    DIV,
    UNKNOWN,
};

enum e_error {
    INCORRECT_OPERAND,
    INCORRECT_OPERATION,
};

enum e_input_type {
    OPERAND1,
    OPERATION,
    OPERAND2,
    RESULT,
};

void mx_printchar(char c);
void mx_printint(int n);
void mx_printstr(const char *s);
void mx_printerr(const char *s);
void mx_strdel(char **str);
void mx_find_inclusive_limits(const char *str, int *max_ptr, int *min_ptr);
void mx_printerror_int(int n);
void mx_del_strarr(char ***arr);
void mx_get_next_step(int *number_ptr, const char *template, int number_max);
int mx_strlen(const char *s);
int mx_atoi(const char *str);
int mx_get_lenght_of_array(char **array);
int mx_perform_operation(enum e_operation operation, int operand1, int operand2);
int mx_solve_equation(int operand1,
                      int operand2,
                      enum e_operation operation,
                      int equal,
                      enum e_input_type unknown_variable);
int mx_find_num_of_digits(int nbr);
int mx_pow(int n, unsigned int pow);
int mx_length_of_input_type_array(enum e_input_type *input_type_array);
bool mx_isdigit(char c);
bool mx_isspace(char c);
bool mx_is_fits_template(int num, const char *template);
char *mx_strnew(const int size);
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strcat(char *s1, const char *s2);
char *mx_strdup(const char *str);
char *mx_strjoin(char const *s1, char const *s2);
char *mx_strtrim(const char *str);
char *mx_decimal_to_string(int nbr);
char **mx_generate_nums_str(const char *template);
char *mx_concat_words(char **words);
char **mx_decrypt_single(const char *operand1,
                         const char *operation,
                         const char *operand2,
                         const char *result,
                         enum e_input_type unknown_variable_enum);
char **mx_join_string_arrays(char **arr1, char **arr2);
char **mx_decrypt_all(const char *operand1,
                      const char *operation,
                      const char *operand2,
                      const char *result,
                      enum e_input_type *unknown_variable_enums,
                      int unknown_variables_count);

enum e_input_type *mx_find_unknown_variables(const char *operand1,
                                             const char *operation,
                                             const char *operand2,
                                             const char *result,
                                             int *array_length);
enum e_input_type *mx_input_type_array_sub(enum e_input_type item,
                                           enum e_input_type *input_type_array,
                                           int array_size);



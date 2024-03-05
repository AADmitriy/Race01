#include <stdlib.h>

#include "minilibmx.h"

enum e_input_type *mx_input_type_array_sub(enum e_input_type item,
                                           enum e_input_type *input_type_array,
                                           int array_size) {
    int new_size = 0;
    for (int i = 0; i < array_size; i++) {
        if (input_type_array[i] != item) {
            new_size++;
        }
    }

    enum e_input_type *new_array = (enum e_input_type*)malloc(sizeof(enum e_input_type) * new_size);
    if (new_array == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < array_size; i++) {
        if (input_type_array[i] != item) {
            new_array[index++] = input_type_array[i];
        }
    }

    return new_array;
}


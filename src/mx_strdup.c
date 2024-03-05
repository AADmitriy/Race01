#include <stdlib.h>

#include "minilibmx.h"

char *mx_strdup(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    int new_str_size = mx_strlen(str);
    char *new_str = mx_strnew(new_str_size);
    
    if (new_str == NULL) {
        return NULL;
    }

    mx_strcpy(new_str, str);

    return new_str;
}


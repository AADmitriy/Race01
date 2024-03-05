#include <stdbool.h>
#include <stdlib.h>

#include "minilibmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    while (mx_isspace(*str) && *str != '\0') {
        str++;
    }

    if (*str == '\0') {
        return mx_strnew(0);
    }

    int str_length = mx_strlen(str);
    int str_real_length = str_length;

    while (mx_isspace(str[str_real_length - 1])) {
        str_real_length--;
    }

    char *trimed_str = mx_strnew(str_real_length);

    mx_strncpy(trimed_str, str, str_real_length);

    return trimed_str;
}


#include <stdlib.h>

#include "minilibmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
    if (s1 == NULL && s2 == NULL) {
        return NULL;
    }

    if (s1 == NULL) {
        char *dupl_str = mx_strdup(s2);
        return dupl_str;
    }

    if (s2 == NULL) {
        char *dupl_str = mx_strdup(s1);
        return dupl_str;
    }

    int s1_size = mx_strlen(s1);
    int s2_size = mx_strlen(s2);

    char *new_str = mx_strnew(s1_size + s2_size);

    mx_strcat(new_str, s1);
    mx_strcat(new_str, s2);

    return new_str;
}


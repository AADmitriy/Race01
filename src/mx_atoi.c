#include <stdbool.h>

#include "minilibmx.h"

int mx_atoi(const char *str) {
    int result = 0;
    int sign = 1;

    while (mx_isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    }
    else if (*str == '+') {
        str++;
    }

    while (mx_isdigit(*str)) {    
        result *= 10;
        result += *str - '0';
        
        str++;
    }

    return result * sign;
}


#include <stdbool.h>

#include "minilibmx.h"

bool mx_is_fits_template(int num, const char *template) {
    int sign = 1;

    int num_max;
    int num_min;
    mx_find_inclusive_limits(template, &num_max, &num_min);

    if (!(num_max >= num && num >= num_min)) {
        return false;
    }
    
    if (*template == '-') {
        sign = -1;
        template++;
    }
    else if (*template == '+') {
        template++;
    }

    if ((sign > 0 && num < 0)
        || (sign < 0 && num > 0)) {
        return false;
    }

    int length = mx_strlen(template);

    for (int i = length - 1; i >= 0; i--) {
        char letter = template[i];
        int digit = num % 10 >= 0 ? num % 10 : -(num % 10);

        if (letter == '?') {
            num /= 10;
            continue;
        }
        if (mx_isdigit(letter) && letter - '0' != digit) {
            return false;
        }
        else {
            num /= 10;
        }
    }

    return true;
}


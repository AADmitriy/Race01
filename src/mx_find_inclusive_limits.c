#include <limits.h>

#include "minilibmx.h"

int find_inclusive_max(const char *str) {
    bool is_negative = (*str == '-');
    int max = 0;

    if (*str == '-' || *str == '+') {
        str++;
    }

    while (*str == '?' || mx_isdigit(*str)) {
        if (mx_isdigit(*str)) {
            if ((!is_negative && INT_MAX / 10 < max)
                || (!is_negative && INT_MAX - *str - '0' < max)
                || (!is_negative && INT_MAX / 10 - *str - '0' < max)
                || (is_negative && INT_MIN / 10 > max)
                || (is_negative && INT_MIN + *str - '0' > max)
                || (is_negative && INT_MIN / 10 + *str - '0' > max)) {
                return is_negative ? INT_MIN : INT_MAX;
            }
            max = is_negative ? max * 10 - (*str - '0') : max * 10 + (*str - '0');
            str++;
        }
        else {
            if ((!is_negative && INT_MAX / 10 < max)
                || (!is_negative && INT_MAX - 9 < max)
                || (!is_negative && INT_MAX / 10 - 9 < max)
                || (is_negative && INT_MIN / 10 > max)) {
                return is_negative ? INT_MIN : INT_MAX;
            }
            max = is_negative ? max * 10 : max * 10 + 9;
            str++;
        }
    }

    return max;
}

int find_inclusive_min(const char *str) {
    bool is_negative = (*str == '-');
    int min = 0;

    if (*str == '-' || *str == '+') {
        str++;
    }

    while (*str == '?') {
        if (is_negative) {
            min = min * 10 - 9;
        }
        str++;
    }

    while (*str != '\0' && (*str == '?' || mx_isdigit(*str))) {
        if (mx_isdigit(*str)) {
            if ((!is_negative && INT_MAX / 10 < min)
                || (!is_negative && INT_MAX - *str - '0' < min)
                || (!is_negative && INT_MAX / 10 - *str - '0' < min)
                || (is_negative && INT_MIN / 10 > min)
                || (is_negative && INT_MIN + *str - '0' > min)
                || (is_negative && INT_MIN / 10 + *str - '0' > min)) {
                return is_negative ? INT_MIN : INT_MAX;
            }
            min = is_negative ? min * 10 - (*str - '0') : min * 10 + (*str - '0');
            str++;
        }
        else {
            if ((!is_negative && INT_MAX / 10 < min)
                || (is_negative && INT_MIN / 10 > min)
                || (is_negative && INT_MIN + 9 > min)
                || (is_negative && INT_MIN / 10 + 9 > min)) {
                return is_negative ? INT_MIN : INT_MAX;
            }
            min = is_negative ? min * 10 - 9 : min * 10;
            str++;
        }
    }

    return min;
}

void mx_find_inclusive_limits(const char *str, int *max_ptr, int *min_ptr) {
    int max = find_inclusive_max(str);
    int min = find_inclusive_min(str);
    
    *max_ptr = max;
    *min_ptr = min;
}


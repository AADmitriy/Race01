#include <stdlib.h>

#include "minilibmx.h"

int mx_find_num_of_digits(int nbr) {
    int num_digits = 1;
    if (nbr < 0) {
        nbr *= -1;
    }
    nbr /= 10;

    while (nbr > 0) {
        nbr /= 10;
        num_digits++;
    }

    return num_digits;
}

char *mx_decimal_to_string(int nbr) {
    int num_of_digits = mx_find_num_of_digits(nbr);
    if (nbr < 0) {
        char *num_str = mx_strnew(num_of_digits + 1);

        if (num_str == NULL) {
            return 0;
        }

        num_str[0] = '-';
        nbr *= -1;
        
        for (int i = num_of_digits; i >= 1; i--) {
            int remainder = nbr % 10;

            num_str[i] = remainder + '0';

            nbr /= 10;
        }

        return num_str;
    }
    
    char *num_str = mx_strnew(num_of_digits);
    if (num_str == NULL) {
        return 0;
    }

    for (int i = num_of_digits - 1; i >= 0; i--) {
        int remainder = nbr % 10;

        num_str[i] = remainder + '0';

        nbr /= 10;
    }

    return num_str;
}


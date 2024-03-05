#include <stdbool.h>

#include "minilibmx.h"

//works with "mx_find_inclusive_limit()"
// assumes that template is trimmed; 
void mx_get_next_step(int *number_ptr, const char *template, int number_max) {
    int sign = 1;

    if (*template == '-') {
        template++;
        
    }
    else if (*template == '+'){
        template++;
    }

    if (*number_ptr < 0) {
        sign = -1;
        
    }
    
    int template_length = mx_strlen(template);

    int number = *number_ptr;
    bool overflow_previous_digit = false;

    for (int i = template_length - 1; i >= 0; i--) {
        if (template[i] == '?') {
            if (number >= 0) {
                int remainder = number % 10;

                if (remainder < 9) {
                    *number_ptr += mx_pow(10, template_length - 1 - i);

                    return;
                }
                else if (remainder == 9) {
                    *number_ptr -= 9 * mx_pow(10, template_length - 1 - i);
                    overflow_previous_digit = true;
                    number /= 10;
                }
            }
            else {
                int remainder = number % 10;
                

                if (remainder < 0) {
                    *number_ptr += mx_pow(10, template_length - 1 - i);

                    return;
                }
                else if (remainder == 0) {
                    *number_ptr -= 9 * mx_pow(10, template_length - 1 - i);
                    overflow_previous_digit = true;
                    number /= 10;
                }
            }
        }
        else {
            number /= 10;
        }
    }

    if (overflow_previous_digit) {
        *number_ptr = number_max + 1;
    }
    *number_ptr += 1;
}


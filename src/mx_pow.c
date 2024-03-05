#include <math.h>

int mx_pow(int n, unsigned int pow) {
    if (pow == 0 || (n == 0 && pow == 0)) {
        return 1;
    }
    
    int result = 1;
    
    while (pow != 0) {
        result *= n;
        pow -= 1;
    }
    
    return result;
}


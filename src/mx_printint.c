#include <unistd.h>

void mx_printint(int n) {
    if (n == -2147483648) {
        write(1, "-2147483648", 11);
        return;
    }
    
    if (n < 0) {
        write(1, "-", 1);
        n *= -1;
    }

    if (n > 9) {
        mx_printint(n / 10);
    }

    char num = n % 10 + '0';
    write(1, &num, 1);
}


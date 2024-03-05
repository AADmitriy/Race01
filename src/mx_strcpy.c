char *mx_strcpy(char *dst, const char *src) {
    char *org_dst = dst;

    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }

    *dst = '\0';

    return org_dst;
}


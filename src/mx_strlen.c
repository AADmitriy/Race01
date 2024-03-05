int mx_strlen(const char *s) {
    int len = 0;    

    while(*s != '\0') {
        len++;
        s++;
    }

    return len;
}


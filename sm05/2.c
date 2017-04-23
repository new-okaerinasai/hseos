void normalize_path(char *buf) {
    char *current = buf;
    char previous = ' ';
    char *tmp = buf;
    for (; *tmp != '\0'; ++tmp) {
        if (*tmp != '/') {
            *current = *tmp;
            ++current;
        }
        if (*tmp == '/') {
            if (previous != '/') {
                *current = *tmp;
                ++current;
            }
        }
        previous = *tmp;
    }
    *current = *tmp;
}

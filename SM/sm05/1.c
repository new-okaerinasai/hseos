int mystrcmp(const char* str1, const char* str2) {    
    const char* tmp1 = str1;
    const char* tmp2 = str2;
    for ( ; *tmp1 == *tmp2; ++tmp1, ++tmp2) {
        if (!*tmp1) {
            return 0;
        }
    }
    return *(unsigned char *) tmp1 - *(unsigned char*) tmp2;
}

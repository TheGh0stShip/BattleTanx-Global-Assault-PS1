unsigned short func_80033DD4(unsigned char *object) {
    unsigned int result = 0;
    unsigned char *entry = *(unsigned char **)(object + 8);

    while (entry != 0) {
        entry = *(unsigned char **)(entry + 0x1C);
        result += 1;
    }
    return result;
}

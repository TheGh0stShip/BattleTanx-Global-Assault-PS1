void *func_8005A2A0(unsigned char *object) {
    unsigned char *entry = *(unsigned char **)(object + 4);
    while (entry[0] != 0) {
        if ((entry[1] & 0x80) != 0) {
            return entry;
        }
        entry += 0x20;
    }
    return 0;
}

int func_80050354(unsigned char *object) {
    unsigned char *entry = *(unsigned char **)(object + 0x1C);
    return entry[0x17] == 7;
}

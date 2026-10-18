void func_80085300(unsigned char *owner, unsigned char *entry, int amount, int index) {
    unsigned char *slot = owner + index * 4;
    *(void **)(entry + 0x0C) = *(void **)(slot + 8);
    *(void **)(slot + 8) = entry;
    *(int *)(owner + 4) += amount;
}

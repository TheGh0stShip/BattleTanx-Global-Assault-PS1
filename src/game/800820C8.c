void *func_8008AA48(void *destination, int value, unsigned int size);

extern unsigned char D_800EDC9C[];

void func_800820C8(void) {
    unsigned char *table = D_800EDC9C;

    func_8008AA48(table, 0, 0x26C);
    *(int *)D_800EDC9C = -1;
    *(int *)(table + 0xC0) = -1;
}

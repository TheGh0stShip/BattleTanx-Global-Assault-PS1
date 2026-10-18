typedef void (*Callback)(int operation, void *value);

extern unsigned char D_800EDC9C[];

void func_80083194(unsigned int *object) {
    unsigned char *table = D_800EDC9C;
    unsigned char *entry = table + object[0] * 4;

    if (*(unsigned int *)(entry + 0x1C8) != 0) {
        Callback callback = *(Callback *)(entry + 0x0C);

        callback(0x0D, (void *)object[2]);
        *(unsigned int *)(entry + 0x1C8) = 0;
        *(unsigned int *)(entry + 0x1F0) = 0;
        *(unsigned int *)(entry + 0x218) = 0;
        *(unsigned int *)(entry + 0x240) = 0;
    }
}

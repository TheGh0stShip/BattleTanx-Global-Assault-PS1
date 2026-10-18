typedef void (*Callback)(int operation, void *value);

extern unsigned char D_800EDC9C[];

void func_8008310C(unsigned int *object) {
    register unsigned char *table asm("$3") = D_800EDC9C;
    Callback callback;

    asm("" : "+r"(table));
    callback = *(Callback *)(table + object[0] * 4 + 0x0C);

    callback(0x10, (void *)object[2]);
}

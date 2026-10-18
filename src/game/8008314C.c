typedef void (*Callback)(int operation, void *value, void *argument);

extern unsigned char D_800EDC9C[];

void func_8008314C(unsigned int *object, void *argument) {
    register unsigned char *table asm("$3") = D_800EDC9C;
    Callback callback;

    asm("" : "+r"(table));
    callback = *(Callback *)(table + object[0] * 4 + 0x0C);
    callback(0x0C, (void *)object[2], argument);
}

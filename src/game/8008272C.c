typedef int (*RuntimeCallback)(int operation, void *first, void *second);

extern unsigned char D_800EDC9C;
extern void func_80081E94(int unused, int *slot, void **first, void **second);

int func_8008272C(int input)
{
    int slot;
    void *first;
    void *second;
    int result = 0;

    func_80081E94(input, &slot, &first, &second);
    if (slot != -1) {
        register unsigned char *base asm("$2") = &D_800EDC9C;
        register unsigned char *entry asm("$3") =
            (unsigned char *)(slot << 2);
        RuntimeCallback callback;

        entry += (int)base;
        callback = *(RuntimeCallback *)(entry + 0x0C);
        result = callback(8, first, second);
    }
    return result;
}

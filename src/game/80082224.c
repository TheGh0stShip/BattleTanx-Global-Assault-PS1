typedef int (*RuntimeCallback)(int operation, void *value);

extern unsigned char D_800EDC9C;
extern void func_80081E94(int input, int *slot, void **value, int unused);

int func_80082224(int input)
{
    int slot;
    void *value;
    int result = 0;

    func_80081E94(input, &slot, &value, 0);
    if (slot != -1) {
        register unsigned char *base asm("$2") = &D_800EDC9C;
        register unsigned char *entry asm("$3") =
            (unsigned char *)(slot << 2);
        RuntimeCallback callback;

        entry += (int)base;
        callback = *(RuntimeCallback *)(entry + 0x0C);
        result = callback(2, value);
    }
    return result;
}

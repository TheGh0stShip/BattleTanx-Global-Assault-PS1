extern unsigned char D_800EDCD8[];
extern void func_8008DA04(unsigned char *destination, const unsigned char *source);
extern int func_80090184(const unsigned char *text);

void func_800831F4(const unsigned char *text) {
    unsigned char *buffer = D_800EDCD8;

    func_8008DA04(buffer, text);
    *(int *)(buffer + 0x80) = func_80090184(text);
}

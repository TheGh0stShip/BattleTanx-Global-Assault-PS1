extern int func_80090184(const unsigned char *text);
extern void func_80086E6C(unsigned char *destination);
extern void func_80094044(
    unsigned char *destination,
    const unsigned char *source,
    int count
);
extern void func_8008AA48(unsigned char *destination, int value, int count);

void func_80086F0C(unsigned char *destination, const unsigned char *text) {
    int length = func_80090184(text);
    if (length >= 9) {
        length = 8;
    }
    func_80086E6C(destination);
    func_80094044(destination + 12, text, length);
    func_8008AA48(destination + 12 + length, 0, 9 - length);
}

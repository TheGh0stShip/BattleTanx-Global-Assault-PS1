extern int func_80090184(const unsigned char *text);
extern void func_8008DA04(unsigned char *destination, const unsigned char *source);

void func_80086F8C(unsigned char *text) {
    if (func_80090184(text) >= 13) {
        func_8008DA04(text, text + 12);
    }
}

extern int D_800C60C0;
extern char *D_800ADE00[];
extern int func_80090184(char *s);
extern char *func_80068F34(int size);
extern void func_8008DA04(char *dst, char *src);
extern void func_80092830(char *a, char *b, int n);
extern void func_8006A8E4(char *a, int b);
extern void func_80068F9C(char *a);

void func_8006AB60(int index) {
    char *buf;
    char *text;

    int slot;

    if (D_800C60C0 & 1) {
        slot = index - 1;
        buf = func_80068F34(func_80090184(D_800ADE00[slot]) + 109);
        text = buf + 108;
        func_8008DA04(text, D_800ADE00[slot]);
        func_80092830(buf, text, 2);
        func_8006A8E4(buf, 1);
        func_80068F9C(buf);
    }
}

extern int func_80097048(int);
extern void func_80097114(void (*)(void));
extern void func_80097128(void (*)(void));
extern void func_800A18D8(void (*)(void));
extern void func_800A18EC(int);
extern void func_800943B0(char *);
extern void func_80096E6C(int, int);
extern char D_800C55A0[];

void func_8009B1EC(void);
void func_8009B214(void);
void func_8009B23C(void);

int func_8009B168(void)
{
    int retry = 4;
    int ret;

loop:
    if (func_80097048(1) == 1) {
        func_80097114(func_8009B1EC);
        func_80097128(func_8009B214);
        func_800A18D8(func_8009B23C);
        func_800A18EC(0);
        ret = 1;
    } else {
        if (retry-- != 0) {
            goto loop;
        }
        func_800943B0(D_800C55A0);
        ret = 0;
    }
    return ret;
}

void func_8009B1EC(void)
{
    func_80096E6C(0xF0000003, 32);
}

void func_8009B214(void)
{
    func_80096E6C(0xF0000003, 64);
}

void func_8009B23C(void)
{
    func_80096E6C(0xF0000003, 64);
}

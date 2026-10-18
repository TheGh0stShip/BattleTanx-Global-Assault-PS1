extern int func_80099DEC(int, int, int);

typedef struct {
    int pad;
    volatile int flags;
} S8008F410;
extern S8008F410 D_800EEDF4;

void func_8008F410(int enable) {
    int mode = func_80099DEC(0, 1, 0);

    if (enable != 0) {
        D_800EEDF4.flags |= 0x20;
        func_80099DEC(1, 1, mode | 0x800);
    } else if (D_800EEDF4.flags & 0x20) {
        func_80099DEC(1, 1, mode & ~0x800);
        D_800EEDF4.flags &= ~0x20;
    }
}

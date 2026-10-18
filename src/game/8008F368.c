extern int func_80099DEC(int, int, int);

typedef struct {
    int pad;
    volatile int flags;
} S8008F368;
extern S8008F368 D_800EEDF4;

void func_8008F368(int enable) {
    int mode = func_80099DEC(0, 1, 0);

    if (enable != 0) {
        if (!(D_800EEDF4.flags & 0x10)) {
            func_80099DEC(1, 1, mode | 0x20);
            D_800EEDF4.flags |= 0x10;
        }
    } else if (D_800EEDF4.flags & 0x10) {
        func_80099DEC(1, 1, mode & ~0x20);
        D_800EEDF4.flags &= ~0x10;
    }
}

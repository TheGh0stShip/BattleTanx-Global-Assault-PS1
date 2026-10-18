extern int func_80099DEC(int, int, int);
extern int func_8008F824(void);

typedef struct {
    char pad0[4];
    volatile int status;
    char pad8[4];
    int flags;
    char pad16[8];
    int (*poll)(void);
} S8008FAA4;
extern S8008FAA4 D_800EEDF4;

int func_8008FAA4(unsigned char c) {
    unsigned int tries = 0;
    int err = tries;

    do {
        if ((func_80099DEC(0, 0, 0) & 0x105) == 0x105) {
            break;
        }
        if (D_800EEDF4.poll != 0) {
            tries++;
            if (tries >= 50) {
                err = D_800EEDF4.poll();
                tries = 0;
                func_8008F824();
            }
        }
        if (D_800EEDF4.status & 8) {
            err = 1;
        }
    } while (err == 0);
    if (err == 0) {
        D_800EEDF4.flags |= 1;
        func_80099DEC(1, 4, c);
    }
    return err;
}

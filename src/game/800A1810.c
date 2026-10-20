extern int func_80088870(int source);
extern void func_800970F4(int enabled, int value);
extern void func_800A1520(int mode);
extern int D_800B90D8;

int func_800A1810(int repeat, int value) {
    register int saved_repeat asm("$18") = repeat;
    register int saved_value asm("$19") = value;
    register volatile int *clock asm("$17") = &D_800B90D8;
    register int result asm("$16");

    asm("" : "+r"(saved_repeat), "+r"(saved_value), "+r"(clock));
    do {
        int now = func_80088870(-1);

        result = -1;
        if (clock[0] + 0x4B0 >= now) {
            if (clock[-2] < 0) {
                func_800A1520(1);
                result = clock[-7];
            } else {
                now = func_80088870(-1);
                if (clock[-1] + 0x3C < now) {
                    func_800A1520(1);
                    result = clock[-7];
                } else {
                    result = clock[-2];
                }
            }
        }
    } while (saved_repeat == 0 && result > 0);
    func_800970F4(1, saved_value);
    return result;
}

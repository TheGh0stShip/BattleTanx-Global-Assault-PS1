extern int D_800B8CB8;
extern int (*D_800B8C74)(int value);
extern int (*D_800BD460[])(int *index);
extern int func_8009ECDC(void);
extern void func_800A3A24(int value);

void func_8009E808(void) {
    register int *index asm("$5") = &D_800B8CB8;
    int current = *index;
    int (*step)(int *) = D_800BD460[current];
    int result;

    asm("" : "+r"(index));
    *index = current + 1;
    result = step(index);
    if (result >= 0) {
        if (D_800B8CB8 != 0) {
            func_800A3A24(0x3C);
            if (func_8009ECDC() == 0) {
                D_800B8C74(-3);
            }
        }
        if (D_800B8CB8 >= 5) {
            D_800B8CB8--;
        }
    } else {
        D_800B8C74(result);
    }
}

extern int D_800B8CB8;
extern int (*D_800BD460[])(int);
extern void (*D_800B8C74)(int);
void func_800A3A24(int);
int func_8009ECDC(void);

void func_8009E808(int arg)
{
    int *step = &D_800B8CB8;
    register int index asm("$3") = *step;
    int (*func)(int) = D_800BD460[index];
    int result;

    *step = index + 1;
    result = func(arg);

    if (result >= 0) {
        if (D_800B8CB8 != 0) {
            func_800A3A24(60);
            if (func_8009ECDC() == 0) {
                D_800B8C74(-3);
            }
        }
        if (D_800B8CB8 > 4) {
            D_800B8CB8--;
        }
    } else {
        D_800B8C74(result);
    }
}

typedef int (*Handler)(int *);
extern int D_800B8CEC;
extern Handler D_800EFCA8[];
extern int D_800EFC68[][4];

void func_8009F628(void)
{
    int n = D_800B8CEC;

    if (n >= 0) {
        if (D_800EFCA8[n](D_800EFC68[n]) != 0) {
            D_800B8CEC--;
        }
    }
}

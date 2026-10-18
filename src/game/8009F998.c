extern int D_800B8D10;
extern char D_800EFCB8[];
void func_8009F74C(int, char *, int);
void func_8009F998(void)
{
    int count = D_800B8D10;

    if (count > 0) {
        func_8009F74C(1, D_800EFCB8, count);
        D_800B8D10 = 0;
    }
}

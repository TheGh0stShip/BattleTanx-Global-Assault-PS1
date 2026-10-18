typedef int (*Handler)(int *);
extern int D_800B8CEC;
extern Handler D_800EFCA8[];
extern int D_800EFC68[][4];
extern char D_800C5D28[];
void func_800943B0(const char *, ...);

void func_8009F5AC(Handler handler)
{
    int n = D_800B8CEC + 1;
    int i;

    if (n >= 4) {
        func_800943B0(D_800C5D28);
    } else {
        D_800B8CEC = n;
        D_800EFCA8[n] = handler;
        for (i = 3; i >= 0; i--) {
            D_800EFC68[n][i] = 0;
        }
    }
}

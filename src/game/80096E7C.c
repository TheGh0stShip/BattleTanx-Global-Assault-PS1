typedef void (*Handler)(void);

extern Handler D_800B6C54[8];
extern int D_800B6C74;
extern int *D_800B6C78;
extern void func_80096F6C(Handler *, int);
extern void func_80094420(int, void (*)(void));

void func_80096ED4(void);
void func_80096F40(int index, Handler handler);

void *func_80096E7C(void)
{
    *D_800B6C78 = 263;
    D_800B6C74 = 0;
    func_80096F6C(D_800B6C54, 8);
    func_80094420(0, func_80096ED4);
    return func_80096F40;
}

void func_80096ED4(void)
{
    int i;

    D_800B6C74++;
    for (i = 0; i < 8; i++) {
        if (D_800B6C54[i] != 0) {
            D_800B6C54[i]();
        }
    }
}

void func_80096F40(int index, Handler handler)
{
    if (handler != D_800B6C54[index]) {
        D_800B6C54[index] = handler;
    }
}

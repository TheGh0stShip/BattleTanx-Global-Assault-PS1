typedef void (*Callback)(void);

extern Callback D_800B6C54[8];
extern int D_800B6C74;
extern int D_800B6C74_write asm("D_800B6C74");
extern int *D_800B6C78;
extern void func_80096F6C(Callback *, int);
extern void func_80094420(int, void *);

void D_80096ED4(void);
void D_80096F40(int index, Callback callback);

void *func_80096E7C(void) {
    void *result;
    Callback hook;
    register Callback *callbacks asm("$4") = D_800B6C54;
    register int *status asm("$3");

    asm volatile("" : "+r"(callbacks));
    status = D_800B6C78;
    asm volatile("" : "+r"(status));
    *status = 0x107;
    D_800B6C74 = 0;
    asm volatile("" ::: "memory");
    func_80096F6C(callbacks, 8);
    hook = D_80096ED4;
    asm volatile("" : "+r"(hook));
    func_80094420(0, hook);
    result = D_80096F40;
    asm volatile("" : "+r"(result));
    return result;
}

void D_80096ED4(void) {
    int index;
    int count;

    count = D_800B6C74;
    index = 0;
    D_800B6C74_write = count + 1;
    do {
        if (D_800B6C54[index] != 0) {
            D_800B6C54[index]();
        }
        index++;
    } while (index < 8);
}

void D_80096F40(int index, Callback callback) {
    if (callback == D_800B6C54[index]) {
        return;
    }
    D_800B6C54[index] = callback;
}

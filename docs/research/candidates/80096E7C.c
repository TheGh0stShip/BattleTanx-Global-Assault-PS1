typedef void (*Callback)(void);

extern Callback D_800B6C54[8];
extern int D_800B6C74;
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
    asm("lw %0,D_800B6C78" : "=r"(status));
    *status = 0x107;
    asm volatile("sw $0,D_800B6C74" ::: "memory");
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
    int count = D_800B6C74;
    register Callback *current asm("$16");

    asm volatile("" : "+r"(count));
    index = 0;
    current = D_800B6C54;
    count++;
    asm volatile("sw %0,D_800B6C74" : : "r"(count) : "memory");
    do {
        if (*current != 0) {
            (*current)();
        }
        index++;
        current++;
    } while (index < 8);
}

void D_80096F40(int index, Callback callback) {
    if (callback == D_800B6C54[index]) {
        return;
    }
    D_800B6C54[index] = callback;
}

extern void func_80094D9C(int);
extern void func_80096008(int);
extern void func_80094DC8(void);

void func_80096E2C(void) {
    register int *global_pointer asm("$28");

    if (global_pointer[4] == 0) {
        global_pointer[4] = 1;
        func_80094D9C(0);
        func_80096008(0);
        func_80094DC8();
    }
}

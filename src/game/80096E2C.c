extern int D_800C6084;
void func_80094D9C(int);
void func_80096008(int);
void func_80094DC8(void);
void func_80096E2C(void) {
    if (D_800C6084 == 0) {
        D_800C6084 = 1;
        func_80094D9C(0);
        func_80096008(0);
        func_80094DC8();
    }
}

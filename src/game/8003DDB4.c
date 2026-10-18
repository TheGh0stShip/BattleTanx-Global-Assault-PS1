extern int D_800A48DC;
extern void *D_800DDDEC;
int func_80085F5C(int);
void func_8007FA74(int);
void func_80068F9C(void *);
void *func_80068F34(int);
void func_8007F708(void *, int);
void func_8007F740(int);

void func_8003DDB4(void) {
    int size = func_80085F5C(-1) - 1024;

    if (D_800A48DC != 0) {
        size -= 32000;
    }
    if (size > 400000) {
        size = 400000;
    }
    func_8007FA74(0);
    if (D_800DDDEC != 0) {
        func_80068F9C(D_800DDDEC);
    }
    D_800DDDEC = func_80068F34(size);
    func_8007F708(D_800DDDEC, size);
    func_8007F740(2);
}

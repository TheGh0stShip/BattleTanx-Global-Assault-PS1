typedef struct {
    volatile int flags;
    void (*cb)(int, int, int, int);
    unsigned char pad[0x1A4];
    int v1AC;
} State;
extern State D_800EEC34;
void func_8008EA00(void);
void func_8008E860(int a0, int a1, int a2, int a3, int a4)
{
    void (*cb)(int, int, int, int);
    D_800EEC34.v1AC = 0;
    if (D_800EEC34.flags & 0x10) {
        D_800EEC34.flags &= ~0x10;
        cb = D_800EEC34.cb;
        if (cb != 0) {
            cb(a1, a2, a3, a4);
        }
    }
    func_8008EA00();
}

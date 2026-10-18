typedef struct Buffer {
    unsigned char busy;
    char pad[3];
    void *data;
} Buffer;

extern unsigned char D_800AE9E8;
extern Buffer D_800EAFC0[];
extern char D_800EAF6C[];
extern unsigned char func_80075570(void);
extern void func_8008314C(void *, int);
extern void func_80082DF4(void *, void *, int, void (*)());
extern void func_80076370();

void func_800762DC(int unused, int start) {
    if (start != 0) {
        D_800AE9E8 = func_80075570();
        D_800EAFC0[D_800AE9E8].busy = 1;
        func_8008314C(D_800EAF6C, 1);
        func_80082DF4(D_800EAF6C, D_800EAFC0[D_800AE9E8].data, 0x28004, func_80076370);
    }
}

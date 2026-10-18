typedef struct Buffer {
    unsigned char busy;
    char pad[3];
    int *data;
} Buffer;

extern unsigned char D_800AEA46;
extern Buffer D_800EAFC0[];
extern int D_800EAFE0;
extern char D_800EAF6C[];
extern char D_800AE9E0[];
extern void func_80082424(void *, int);
extern unsigned int func_80085F5C(int);
extern int *func_80068F34(int);
extern void func_8008314C(void *, int);
extern void func_80082798(void *, int, int);
extern void func_80082854(void *, void *, int);
extern void func_8007FC88(void *, void *);
extern void func_8007FA74(int);
extern void func_800826A0(void *);
extern void func_80068F9C(void *);

void func_80076060(int mode, unsigned char track) {
    if (D_800AEA46 == track) {
        return;
    }
    D_800AEA46 = track;
    func_80082424(D_800EAF6C, mode);
    if (func_80085F5C(-1) > 0x28004) {
        D_800EAFC0[0].data = func_80068F34(0x28004);
        D_800EAFC0[0].data[0] = 0;
        D_800EAFC0[0].busy = 0;
    }
    func_8008314C(D_800EAF6C, 1);
    func_80082798(D_800EAF6C, (track - 1) * 0x28004, 0);
    func_8008314C(D_800EAF6C, 1);
    func_80082854(D_800EAF6C, D_800EAFC0[0].data, 0x28004);
    func_8007FC88(D_800AE9E0, D_800EAFC0[0].data + 1);
    func_8007FA74(0);
    D_800EAFE0 = D_800EAFC0[0].data[0];
    func_800826A0(D_800EAF6C);
    func_80068F9C(D_800EAFC0[0].data);
}

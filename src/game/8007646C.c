typedef struct Buffer {
    unsigned char busy;
    char pad[3];
    void *data;
} Buffer;

extern unsigned char D_800AE9E9;
extern unsigned char D_800AE9EA;
extern Buffer D_800EAFC0[];
extern char D_800EAF6C[];
extern void func_80083194(void *);
extern void func_800826A0(void *);
extern void func_80068F9C(void *);

void func_8007646C(void) {
    unsigned char i;

    func_80083194(D_800EAF6C);
    func_800826A0(D_800EAF6C);
    for (i = 0; i < D_800AE9E9; i++) {
        func_80068F9C(D_800EAFC0[i].data);
    }
    D_800AE9EA = 0;
}

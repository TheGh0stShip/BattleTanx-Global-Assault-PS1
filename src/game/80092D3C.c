extern void func_800919D8(void);
extern void func_80091984(void);
extern void func_800916F4(void);
extern int func_800982B0(int, unsigned int *, int *);
extern void func_8009759C(unsigned int, unsigned char *);
extern int func_800973AC(int, unsigned char *, unsigned char *);
extern void func_8009194C(void);
extern int func_8009CA3C(int);

typedef struct {
    char pad[104];
    int file;
} Info80092D3C;
extern Info80092D3C *D_800EEF18;
extern int D_800C60BC;

int func_80092D3C(void) {
    unsigned char loc[8];
    unsigned int pos;
    int size;
    int failed;

    func_800919D8();
    func_80091984();
    func_800916F4();
    failed = func_800982B0(D_800EEF18->file, &pos, &size) == 0;
    if (!failed) {
        D_800C60BC = 1;
        func_8009759C(pos >> 11, loc);
        failed = func_800973AC(2, loc, 0) == 0;
        if (!failed) {
            failed = func_800973AC(21, 0, 0) == 0;
            if (!failed) {
                func_8009194C();
                failed = func_8009CA3C(480) == 0;
            }
        }
    }
    return failed ^ 1;
}

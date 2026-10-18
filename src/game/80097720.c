extern int D_800C60BC;
extern void func_8009759C(int, unsigned char *);
extern int func_800973AC(int, unsigned char *, unsigned char *);
extern int func_8009702C(void);
extern void func_80088870(int);
extern int func_800A1710(int, void *, int);
extern int func_800A1810(int, int);

int func_80097720(void *buf, int sector, int count) {
    unsigned char loc[8];
    int failed;

    D_800C60BC = 1;
    func_8009759C(sector, loc);
    failed = func_800973AC(2, loc, 0) == 0;
    if (!failed) {
        if (!(func_8009702C() & 0x80)) {
            func_80088870(0);
            func_80088870(0);
            func_80088870(0);
            func_80088870(0);
        }
        failed = func_800A1710(count, buf, 128) == 0;
        if (!failed) {
            failed = func_800A1810(0, 0) != 0;
        }
    }
    return failed ^ 1;
}

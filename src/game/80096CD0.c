extern int func_8009AED4(int);
extern int D_800EF050;
extern int D_800EF054;
extern int D_800EF058;
extern int D_800EF05C;
extern volatile int D_800EF080;
extern volatile int D_800EF084;
extern volatile int D_800EF088;
extern volatile int D_800EF08C;

int func_80096CD0(void) {
    int r;

    do {
        r = D_800EF080 + D_800EF084 * 2 + D_800EF088 * 4 + D_800EF08C * 8;
    } while (r == 0);
    func_8009AED4(D_800EF050);
    func_8009AED4(D_800EF054);
    func_8009AED4(D_800EF058);
    func_8009AED4(D_800EF05C);
    D_800EF080 = D_800EF084 = D_800EF088 = D_800EF08C = 0;
    return r >> 1;
}

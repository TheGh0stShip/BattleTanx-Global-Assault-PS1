extern int D_800EBC3C;
extern int D_800AEB30;

int func_80078FA4(void) {
    if (D_800EBC3C == 1) {
        D_800EBC3C = 0;
        D_800AEB30 = 0;
        return 1;
    }
    return 0;
}

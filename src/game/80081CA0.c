extern volatile unsigned long *D_800B0D34;
extern volatile unsigned long *D_800B0D38;

int func_80081CA0(int mode) {
    *D_800B0D38 = 0x10000007;
    if ((*D_800B0D34 & 0xFFFFFF) != 2) {
        *D_800B0D34 = (*D_800B0D38 & 0x3FFF) | 0xE1001000;
        *D_800B0D34;
        return 0;
    }
    if (!(mode & 8)) {
        return 1;
    }
    *(unsigned long *)D_800B0D38 = 0x09000001;
    return 2;
}

extern int D_800A6070;
extern int D_800AE290[];

int func_80022ADC(void) {
    int i = 0;

    switch (D_800A6070) {
    case 3:
        i = 0;
        break;
    case 4:
        i = 1;
        break;
    case 5:
        i = 2;
        break;
    case 6:
        i = 3;
        break;
    case 7:
        i = 4;
        break;
    case 8:
        i = 5;
        break;
    }
    return D_800AE290[i + 289];
}

typedef struct Dialog {
    char data[0x400];
} Dialog;

extern unsigned char D_800D2FEC;
extern int D_800AD9E4;
extern Dialog D_800ABD60;
extern Dialog D_800AC080;
extern unsigned int D_800E5330;
extern unsigned int D_800E5334;
extern int D_800E5308;
extern int D_800E530C;
extern void func_80054A30(int);
extern void func_80054D4C(void);

int func_80064CF8(void) {
    unsigned int target0;
    unsigned int target1;
    int current;
    int limit;

    if (D_800D2FEC == 1) {
        if (D_800AD9E4 == 0) {
            D_800ABD60.data[0xC0] = 4;
            D_800ABD60.data[0x120] = 7;
            func_80054A30(0);
            D_800AD9E4 = 1;
        }
        D_800E5308 += (D_800E5330 + 30) / 30;
        if (D_800E5308 >= D_800E5330) {
            D_800E5308 = D_800E5330;
            func_80054D4C();
            func_80054A30(11);
            func_80054A30(36);
            D_800AD9E4 = 0;
            return 1;
        }
        return 0;
    }
    if (D_800AD9E4 == 0) {
        D_800AC080.data[0xA0] = 4;
        D_800AC080.data[0x100] = 7;
        D_800AC080.data[0x180] = 4;
        D_800AC080.data[0x1E0] = 7;
        func_80054A30(0);
        D_800AD9E4 = 1;
    }
    target0 = D_800E5330;
    if (target0 != 0) {
        D_800E5308 += (target0 + 30) / 30;
    }
    target1 = D_800E5334;
    if (target1 != 0) {
        D_800E530C += (target1 + 30) / 30;
    }
    if (target1 < target0) {
        current = D_800E5308;
        limit = target0;
    } else {
        limit = target1;
        current = D_800E530C;
    }
    if (current < limit) {
        return 0;
    }
    D_800E5308 = D_800E5330;
    D_800E530C = D_800E5334;
    func_80054D4C();
    func_80054A30(11);
    func_80054A30(36);
    D_800AD9E4 = 0;
    return 1;
}

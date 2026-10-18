extern unsigned int D_800A6070;
extern unsigned char D_800AACE0;
extern unsigned char D_800ABA5B;
extern signed char D_800A606C;
extern short D_800AACDC;
extern int D_800EAFBC;
extern char D_800A68A0[];
extern char D_800AA208[];
extern char D_800AA978[];
extern char D_800A6B48[];
extern void func_8003C638(void);
extern void func_800597B4(void *, void *, int);
extern void func_80059550(void *, void *, int);

void func_8005ACC4(void) {
    if (D_800A6070 >= 10) {
        D_800A6070 = 1;
    }
    if (D_800AACE0 != 0) {
        D_800AACE0 = 0;
    } else {
        func_8003C638();
    }
    if (D_800ABA5B != 0) {
        char *root = D_800A68A0;

        func_800597B4(root, 0, 1);
        if (D_800A606C == 1) {
            func_800597B4(D_800AA208, root, 1);
            func_80059550(D_800A6B48, D_800AA208, 1);
        } else {
            func_800597B4(D_800AA978, root, 1);
            func_80059550(D_800A6B48, D_800AA978, 1);
        }
        D_800EAFBC = 6;
    } else {
        func_80059550(D_800A68A0, 0, 1);
    }
    D_800AACDC = 0;
}

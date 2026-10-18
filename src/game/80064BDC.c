typedef struct Element {
    int pad[2];
    int *style;
} Element;

typedef struct Rows {
    char pad0[0x21];
    unsigned char flag0;
    char pad1[0x1F];
    unsigned char flag1;
    char pad2[0x1F];
    unsigned char flag2;
} Rows;

extern int D_800ABA84;
extern int D_800AD86C;
extern int D_800AD7B8;
extern int D_800AD92C;
extern Rows D_800AD888;
extern int D_800EAF38;
extern char D_800A4381;
extern int func_80022814(void);
extern int func_80022994(void);
extern void func_80054D4C(void);
extern void func_8006AFFC(int);
extern void func_80059550(void *, void *, int);
extern Element *func_8005A2A0(void *);
extern void func_8005A54C(void *);

void func_80064BDC(void *menu) {
    void *group;

    if (D_800ABA84 != 0) {
        if (func_80022814()) {
            func_80054D4C();
            func_8006AFFC(0);
            if (func_80022994() == 0) {
                func_80059550(&D_800AD86C, menu, 1);
            } else {
                group = &D_800AD7B8;
                func_80059550(group, menu, 1);
                if (func_8005A2A0(group)->style != &D_800EAF38) {
                    do {
                        func_8005A54C(group);
                    } while (func_8005A2A0(group)->style != &D_800EAF38);
                }
            }
            D_800A4381 = 0;
        } else {
            func_80054D4C();
            func_8006AFFC(0);
            D_800AD888.flag0 = 0x90;
            D_800AD888.flag1 = 16;
            D_800AD888.flag2 = 16;
            func_80059550(&D_800AD92C, menu, 1);
        }
    }
}

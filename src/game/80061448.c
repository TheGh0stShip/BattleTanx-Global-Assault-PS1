typedef struct Cursor {
    short *value;
} Cursor;

extern unsigned short D_800E4D6C;
extern int D_800A6070;
extern unsigned char D_800D2FEC;
extern Cursor D_800AB118;
extern Cursor D_800AB2B8;
extern Cursor D_800AB458;
extern short D_800ABA54[];
extern void func_8006AC7C(int);
extern void func_80061E38(void);
extern void func_80059550(void *, void *, int);
extern void func_8003A200(int);

void func_80061448(void) {
    if (D_800E4D6C == 0 && D_800A6070 != 10) {
        D_800E4D6C = 1;
        func_8006AC7C(1);
        func_80061E38();
        switch (D_800D2FEC) {
        case 1:
            D_800AB118.value = &D_800ABA54[0];
            func_80059550(&D_800AB118, 0, 1);
            break;
        case 2:
            D_800AB2B8.value = &D_800ABA54[0];
            D_800AB458.value = &D_800ABA54[1];
            func_80059550(&D_800AB2B8, 0, 1);
            func_80059550(&D_800AB458, 0, 1);
            break;
        default:
            D_800AB118.value = &D_800ABA54[0];
            func_80059550(&D_800AB118, 0, 1);
            break;
        }
        switch (D_800D2FEC) {
        case 1:
            func_8003A200(1);
            break;
        case 2:
            func_8003A200(2);
            break;
        }
    }
}

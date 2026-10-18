typedef struct Item {
    char pad[0x14];
    unsigned short index;
} Item;

extern unsigned char D_800AACE5;
extern int D_800EAFBC;
extern signed char D_800E482C;
extern signed char D_800E483C;
extern signed char D_800E4824;
extern int D_800EC0F8[];
extern int *D_800A967C;
extern int D_800EAD64;
extern int D_800EADD0;
extern int func_8008623C(int);
extern void func_80086270(int, int);

int func_8005FDA4(Item *item) {
    if (D_800AACE5 == 1) {
        D_800EAFBC = 5;
    }
    D_800EC0F8[D_800E482C] = D_800E483C;
    if (func_8008623C(D_800E482C)) {
        if (D_800E4824) {
            func_80086270(D_800E482C, 1);
            D_800A967C = &D_800EAD64;
        } else {
            func_80086270(item->index, 0);
            D_800A967C = &D_800EADD0;
        }
    }
    return 1;
}

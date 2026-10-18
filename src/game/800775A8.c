extern int D_800C60CC;
extern int D_800EBC48;
extern void *D_800AE990;
extern void *D_800AE994;
extern void *D_800AE998;
extern char D_800AEA58[];
extern void func_80056E48(void *, int, int, int, int, int, int, int, int, void *);

void func_800775A8(void) {
    int y = 50;
    int x = 200;

    if (D_800C60CC == 1) {
        y = 80;
        x = 304;
    }
    if (D_800EBC48 == 2) {
        func_80056E48(D_800AE994, 3, y, 120, 4096, 4096, x, 2, -1, D_800AEA58);
    } else if (D_800EBC48 == 3) {
        func_80056E48(D_800AE998, 3, y, 120, 4096, 4096, x, 2, -1, D_800AEA58);
    } else if (D_800EBC48 == 0) {
        func_80056E48(D_800AE990, 3, y, 120, 4096, 4096, x, 2, -1, D_800AEA58);
    }
}

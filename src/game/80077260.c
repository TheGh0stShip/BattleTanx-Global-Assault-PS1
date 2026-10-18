extern int D_800C60CC;
extern int D_800EBC38;
extern void *D_800AE964[];
extern char D_800AEA4C[];
extern char D_800AEA54[];
extern char D_800AEA58[];
extern void func_80056E48(void *, int, int, int, int, int, int, int, int, void *);

void func_80077260(void) {
    unsigned short x = 190;
    int y = 30;
    int row = 110;

    if (D_800C60CC == 1) {
        x = 304;
        y = 80;
        row = 200;
    }
    func_80056E48(D_800AE964[8], 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
    if (D_800EBC38 != 0) {
        func_80056E48(D_800AE964[9], 3, row, 140, 4096, 4096, x, 0, -1, D_800AEA58);
        func_80056E48(D_800AE964[10], 3, row + 50, 140, 4096, 4096, x, 0, -1, D_800AEA54);
    } else {
        func_80056E48(D_800AE964[9], 3, row, 140, 4096, 4096, x, 0, -1, D_800AEA54);
        func_80056E48(D_800AE964[10], 3, row + 50, 140, 4096, 4096, x, 0, -1, D_800AEA58);
    }
}

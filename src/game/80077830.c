typedef struct PadState {
    unsigned char ready;
    unsigned char port;
} PadState;

extern int D_800C60CC;
extern int D_800EBC38;
extern PadState D_800EBBB4;
extern void *D_800AE964[];
extern void *D_800AE974;
extern void *D_800AE978;
extern char D_800AEA4C[];
extern char D_800AEA54[];
extern char D_800AEA58[];
extern void func_80056E48(void *, int, int, int, int, int, int, int, int, void *);

static inline void draw_confirm(int y, unsigned short x, int row) {
    func_80056E48(D_800AE964[14], 3, y, 120, 4096, 4096, x, 0, -1, D_800AEA4C);
    if (D_800EBC38 != 0) {
        func_80056E48(D_800AE964[9], 3, row, 140, 4096, 4096, x, 0, -1, D_800AEA58);
        func_80056E48(D_800AE964[10], 3, row + 50, 140, 4096, 4096, x, 0, -1, D_800AEA54);
    } else {
        func_80056E48(D_800AE964[9], 3, row, 140, 4096, 4096, x, 0, -1, D_800AEA54);
        func_80056E48(D_800AE964[10], 3, row + 50, 140, 4096, 4096, x, 0, -1, D_800AEA58);
    }
}

void func_80077830(void) {
    unsigned short x = 190;
    int y = 30;
    int row = 110;

    if (D_800C60CC == 1) {
        x = 304;
        y = 80;
        row = 200;
    }
    if (D_800EBBB4.port == 0) {
        func_80056E48(D_800AE974, 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
    } else {
        func_80056E48(D_800AE978, 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
    }
    draw_confirm(y, x, row);
}

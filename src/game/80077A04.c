extern int D_800C60CC;
extern int D_800EBC40;
extern void *D_800AE964[];
extern void *D_800AE9A4;
extern char D_800AEA4C[];
extern void func_80056E48(void *, int, int, int, int, int, int, int, int, void *);

static inline void draw_with_footer(int index, short y, unsigned short x) {
    func_80056E48(D_800AE964[index], 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
    func_80056E48(D_800AE964[20], 3, y, 120, 4096, 4096, x, 0, -1, D_800AEA4C);
}

void func_80077A04(void) {
    unsigned short x = 190;
    int y = 30;

    if (D_800C60CC == 1) {
        x = 304;
        y = 80;
    }
    if (D_800EBC40 == 1) {
        func_80056E48(D_800AE9A4, 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
    } else if (D_800EBC40 == 3) {
        draw_with_footer(18, y, x);
    } else if (D_800EBC40 == 2) {
        draw_with_footer(17, y, x);
    } else if (D_800EBC40 == 4) {
        draw_with_footer(19, y, x);
    }
}

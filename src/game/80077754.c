typedef struct PadState {
    unsigned char pad0;
    unsigned char port;
} PadState;

extern int D_800C60CC;
extern PadState D_800EBBB4;
extern int D_800EBC3C;
extern void *D_800AE974;
extern void *D_800AE978;
extern char D_800AEA4C[];
extern int func_80088324(int, int);
extern void func_80056E48(void *, int, int, int, int, int, int, int, int, void *);

void func_80077754(void) {
    int x = 190;
    int y = 30;
    PadState *pad;

    if (D_800C60CC == 1) {
        x = 304;
        y = 80;
    }
    pad = &D_800EBBB4;
    if (!(func_80088324(2, pad->port) & 2)) {
        if (pad->port == 0) {
            func_80056E48(D_800AE974, 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
        } else {
            func_80056E48(D_800AE978, 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
        }
    } else {
        D_800EBC3C = 2;
    }
}

typedef struct PadState {
    unsigned char pad0;
    unsigned char port;
} PadState;

extern int D_800C60CC;
extern PadState D_800EBBB4;
extern int D_800EBC3C;
extern char *D_800AE96C;
extern char D_800C3E5C[];
extern char D_800C3E60[];
extern char D_800AEA4C[];
extern int func_80088324(int, int);
extern char *func_8008DA04(char *, char *);
extern char *func_8008D954(char *, char *);
extern void func_80056E48(void *, int, int, int, int, int, int, int, int, void *);

void func_80077660(void) {
    int x = 190;
    int y = 30;
    PadState *pad;
    char text[64];

    if (D_800C60CC == 1) {
        x = 304;
        y = 80;
    }
    pad = &D_800EBBB4;
    if (!(func_80088324(2, pad->port) & 1)) {
        func_8008DA04(text, D_800AE96C);
        if (pad->port == 0) {
            func_8008D954(text, D_800C3E5C);
        } else {
            func_8008D954(text, D_800C3E60);
        }
        func_80056E48(text, 3, y, 100, 4096, 4096, x, 0, -1, D_800AEA4C);
    } else {
        D_800EBC3C = 2;
    }
}

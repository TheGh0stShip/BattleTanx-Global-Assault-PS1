typedef struct {
    char pad0[0x12];
    short link;
} Entry;
extern Entry *D_800E4658;
extern int D_800E46BC;
extern void func_800907C4(int, int);

void func_80054D4C(void) {
    unsigned char i;

    for (i = 0; i < 57; i++) {
        D_800E4658[i].link = -1;
    }
    func_800907C4(0, 0xFFFFFF);
    if (D_800E46BC != 0) {
        D_800E46BC = 0;
    }
}

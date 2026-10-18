typedef struct SpuState {
    int a;
    short b;
    short c;
    int d;
    int e;
} SpuState;

extern void func_800943F0();
extern void func_8009A07C(int);
extern void func_8009AB5C(void);
extern void func_8009A87C(int, int, int);
extern unsigned short D_800B778C[24];
extern int D_800B7764;
extern int D_800B7768;
extern int D_800B776C;
extern SpuState D_800B7774;
extern int D_800BD114;
extern int D_800B7BD0;
extern int D_800B7BD4;
extern int D_800B7BD8;
extern int D_800B7760;
extern int D_800B770C;
extern int D_800B775C;
extern int D_800B7788;
extern int D_800B7784;
extern int D_800B7BBC;

void func_8009AA74(int mode) {
    unsigned short *notes;
    int i;

    func_800943F0();
    func_8009A07C(mode);
    if (mode == 0) {
        notes = D_800B778C;
        for (i = 0; i < 24; i++) {
            notes[i] = 0xC000;
        }
    }
    func_8009AB5C();
    D_800B7764 = 0;
    D_800B7768 = 0;
    D_800B7774.a = 0;
    D_800B7774.b = 0;
    D_800B7774.c = 0;
    D_800B7774.d = 0;
    D_800B7774.e = 0;
    D_800B776C = D_800BD114;
    func_8009A87C(0xD1, D_800BD114, 0);
    D_800B7BD0 = 0;
    D_800B7BD4 = 0;
    D_800B7BD8 = 0;
    D_800B7760 = 0;
    D_800B770C = 0;
    D_800B775C = 0;
    D_800B7788 = 0;
    D_800B7784 = 0;
    D_800B7BBC = 0;
    __asm__ volatile("");
}

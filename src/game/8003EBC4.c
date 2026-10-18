extern int D_800A48A8;
extern void func_8003EC24(void);
extern void func_8003ED90(void);

void func_8003EBC4(void) {
    if (D_800A48A8 == 2 || D_800A48A8 == 4) {
        func_8003EC24();
    }
    if (D_800A48A8 == 3 || D_800A48A8 == 4) {
        func_8003ED90();
    }
}

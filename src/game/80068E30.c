extern int D_800ADCF8;
extern int *D_800ADD00;
extern void *D_800ADD0C;
extern void func_80068E70(void);
extern void *func_80085F5C(int value);

void func_80068E30(void) {
    register unsigned char *base asm("$16");

    func_80068E70();
    base = (unsigned char *)0x800B0000;
    __asm__("" : "+r"(base));
    *(void **)(base - 0x22F4) = func_80085F5C(-1);
    D_800ADD00 = &D_800ADCF8;
}

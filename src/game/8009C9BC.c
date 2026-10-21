extern void func_80094198(void);
extern void func_800A3090(int value);
extern void func_800A307C(int value);
extern void func_80097558(int value);
extern void func_80097128(int value);
extern void func_80094168(void);
extern volatile int func_800B8D48;
extern unsigned char * volatile D_800B8BAC;
extern unsigned char * volatile D_800B8BB8;

void func_8009C9BC(void) {
    register int mode asm("$3");

    func_80094198();
    asm volatile("lui %0,%%hi(func_800B8D48)\n\t"
                 "lw %0,%%lo(func_800B8D48)(%0)"
                 : "=r"(mode));
    if (mode == 1) {
        func_800A3090(0);
        func_800A307C(0);
    } else {
        func_80097558(0);
        func_80097128(0);
    }
    asm volatile("" : : : "memory");
    *D_800B8BAC = 0;
    {
        register unsigned char *value asm("$2") = D_800B8BB8;
        asm volatile("nop" : "=r"(value) : "0"(value));
        *value = 0;
    }
    func_80094168();
}

extern unsigned char D_800EEE3C[];

void func_8008AA48(void *destination, int value, int size);
void func_8009B168(void);
void func_80091580(void);
void func_800915AC(void);
void func_800915D8(void);
void func_80097114(void (*callback)(void));
void func_80097558(void (*callback)(void));
void func_80097128(void (*callback)(void));
void func_800973AC(int first, int second, int third);
int func_8009B04C(int value);

void func_80091774(void) {
    register unsigned char *base asm("$2") = (unsigned char *)0x800F0000;
    register unsigned char *state asm("$16");

    asm("" : "+r"(base));
    asm("addiu $16,$2,%%lo(D_800EEE3C)" : "=r"(state) : "r"(base));
    func_8008AA48(state, 0, 0x28);
    asm("sw $0,0x48($28)" : : : "memory");
    func_8009B168();
    func_80097114(func_80091580);
    func_80097558(func_800915AC);
    func_80097128(func_800915D8);
    func_800973AC(1, 0, 0);
    if (func_8009B04C(1) == 2) {
        state[4] = 1;
    }
    *(int *)(state + 0x14) = 0;
}

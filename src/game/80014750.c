extern unsigned char D_800AEA45;
extern unsigned char D_800AEA41;
extern unsigned char D_800AACE1;
extern unsigned char D_800AAD00;
extern int D_80086058;
void func_8007E8F0(void);
void func_800869B0(int);
void func_80075E60(void);

void func_80014750(int unused, int arg) {
    func_8007E8F0();
    func_800869B0(arg);
    if (D_800AEA45 != 0 || D_800AEA41 != 0 || D_800AACE1 != 0 || D_800AAD00 == 1) {
        func_80075E60();
    }
    if (D_80086058 != 0) {
        __asm__ volatile("break 0x400");
    }
}

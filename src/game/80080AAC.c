extern unsigned long *D_800B0D48;
extern unsigned long *D_800B0D4C;
extern unsigned long *D_800B0D50;
extern unsigned long *D_800B0D54;
extern void func_80081B28(void);
extern int func_80081B5C(void);

int func_80080AAC(unsigned long *addr, int size) {
    *D_800B0D54 |= 0x08000000;
    *D_800B0D50 = 0;
    *D_800B0D48 = (unsigned long)&addr[size - 1];
    *D_800B0D4C = size;
    *D_800B0D50 = 0x11000002;
    func_80081B28();
    if (*D_800B0D50 & 0x01000000) { while (*D_800B0D50 & 0x01000000) { if (func_80081B5C()) return -1; } }
    return size;
}

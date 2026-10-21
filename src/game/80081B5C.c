extern int func_80088870(int a);
extern int func_800944F4(int a);
extern void func_800943B0(char *fmt, ...);
extern volatile int D_800B0D6C;
extern volatile int D_800B0D70;
extern volatile int D_800B0D58;
extern volatile int D_800B0D5C;
extern int D_800B0D68;
extern volatile unsigned long *D_800B0D38;
extern volatile unsigned long *D_800B0D3C;
extern volatile unsigned long *D_800B0D44;
extern volatile unsigned long *D_800B0D54;
extern char D_800C4CCC[];

static inline int bump(volatile int *counter) {
    int v = *counter;
    int old = v;

    v++;
    *counter = v;
    return old;
}

int func_80081B5C(void) {
    if (D_800B0D6C < func_80088870(-1) || bump(&D_800B0D70) > 0xF0000) {
        *D_800B0D38;
        func_800943B0(D_800C4CCC, (D_800B0D58 - D_800B0D5C) & 0x3F, *D_800B0D38, *D_800B0D44, *D_800B0D3C);
        D_800B0D68 = func_800944F4(0);
        D_800B0D58 = D_800B0D5C = 0;
        *D_800B0D44 = 0x401;
        *D_800B0D54 |= 0x800;
        *D_800B0D38 = 0x02000000;
        *D_800B0D38 = 0x01000000;
        func_800944F4(D_800B0D68);
        return -1;
    }
    return 0;
}

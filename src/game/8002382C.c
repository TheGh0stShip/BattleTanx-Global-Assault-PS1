typedef unsigned short u16;

extern unsigned char *D_800D3258;
extern u16 D_800D325C;
extern int D_800A4388;
extern int D_800A438C;

void func_8002382C(unsigned char *entry) {
    register unsigned char *slot_base asm("$5") = (unsigned char *)0x800D0000;
    register unsigned char *pointer_base asm("$2");
    register unsigned int old asm("$3");
    register unsigned char *base asm("$2");

    asm("" : "+r"(slot_base));
    asm("lui $2,0x800D" : "=r"(pointer_base));
    old = *(u16 *)(slot_base + 0x325C);
    base = *(unsigned char **)(pointer_base + 0x3258);
    *(u16 *)(entry + 2) = old;
    *(u16 *)(slot_base + 0x325C) = (entry - base) >> 6;
    D_800A4388++;
    D_800A438C--;
}

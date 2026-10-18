extern int D_800D2FE0;

void func_8004D078(unsigned char *entry) {
    register int state asm("$3") = D_800D2FE0;

    asm("" : "+r"(state));
    *(unsigned short *)(entry + 0x00) = 0xFFFF;
    *(unsigned short *)(entry + 0x08) = 0;
    *(int *)(entry + 0x0C) = 0;
    *(int *)(entry + 0x18) = 0;
    *(int *)(entry + 0x10) = 0;
    asm("" : : : "memory");
    *(int *)(entry + 0x04) = state;
}

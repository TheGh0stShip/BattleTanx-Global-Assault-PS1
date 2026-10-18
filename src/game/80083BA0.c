extern unsigned char D_800EDF78[];
extern unsigned char D_800EE028[];

void func_8008AA48(void *destination, int value, int size);
void func_80085258(unsigned int index);

void func_80083BA0(void) {
    register unsigned char *state asm("$16") = D_800EDF78;
    register unsigned int index asm("$17");
    register unsigned char *base asm("$2");

    func_8008AA48(state, 0, 0xB0);
    *(unsigned int *)(state + 0x4C) = 1;
    state[0x50] = 0x40;
    *(unsigned int *)(state + 0x54) = 0;
    func_8008AA48(D_800EE028, 0, 0x460);

    index = 0;
    do {
        *(unsigned int *)(state + 0x64) = 0;
        func_80085258(index);
        index++;
        state += 4;
    } while (index < 8);

    base = D_800EDF78;
    asm("" : "+r"(base));
    *(signed short *)(base + 0xA4) = -32768;
    *(signed short *)(base + 0xA6) = 32767;
    *(signed short *)(base + 0xA8) = -32768;
    *(signed short *)(base + 0xAA) = 32767;
    *(signed short *)(base + 0xAC) = 1;
    *(signed short *)(base + 0xAE) = 1;
}

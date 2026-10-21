extern unsigned int * volatile D_800B8B80;
extern unsigned int *D_800B8BA0;
extern unsigned char D_800C5AB4;
extern void func_8009C938(void *message);

int func_8009C88C(void) {
    volatile int counter = 0x100000;
    register int sentinel asm("$4") = -1;

    asm("" : "+r"(sentinel));
    if ((*D_800B8B80 & 0x01000000) != 0) {
        do {
            counter--;
            if (counter == sentinel) {
                func_8009C938(&D_800C5AB4);
                return -1;
            }
        } while ((*D_800B8B80 & 0x01000000) != 0);
    }
    return 0;
}

unsigned int func_8009C920(void) {
    return *D_800B8BA0;
}

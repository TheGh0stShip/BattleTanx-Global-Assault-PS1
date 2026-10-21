typedef signed int s32;
typedef unsigned int u32;

extern volatile u32 *D_800B8BA0;
extern char D_800C5AA4;
extern void func_8009C938(void *);

s32 func_8009C7F8(void) {
    volatile s32 timeout = 0x100000;

    if (*D_800B8BA0 & 0x20000000) {
        register s32 expired asm("$4") = -1;
        do {
            timeout--;
            if (timeout == expired) {
                func_8009C938(&D_800C5AA4);
                return -1;
            }
            __asm__ volatile ("" ::: "$5");
        } while (*D_800B8BA0 & 0x20000000);
    }
    return 0;
}

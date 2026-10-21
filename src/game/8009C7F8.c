typedef signed int s32;
typedef unsigned int u32;

extern volatile u32 *volatile D_800B8BA0;
extern char D_800C5AA4;
extern void func_8009C938(void *);

static __inline__ u32 read_status_loop(void) {
    register volatile u32 *status asm("$2");
    asm volatile("lw %0,D_800B8BA0" : "=r"(status));
    return *status;
}

s32 func_8009C7F8(void) {
    volatile s32 timeout;
    s32 remaining;
    register volatile u32 *status asm("$3");
    register s32 initial_timeout asm("$2");

    asm("lw %0,D_800B8BA0" : "=r"(status));
    asm("lui %0,0x10" : "=r"(initial_timeout) : "r"(status));
    timeout = initial_timeout;
    if (*status & 0x20000000) {
        register s32 expired asm("$4") = -1;
        do {
            remaining = timeout - 1;
            timeout = remaining;
            remaining = timeout;
            if (remaining == expired) {
                register char *context asm("$4");
                asm("lui %0,0x800C" : "=r"(context));
                context += 0x5AA4;
                func_8009C938(context);
                return -1;
            }
        } while (read_status_loop() & 0x20000000);
    }
    return 0;
}

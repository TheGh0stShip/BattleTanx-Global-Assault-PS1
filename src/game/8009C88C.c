typedef signed int s32;
typedef unsigned int u32;

extern volatile u32 *volatile D_800B8B80;
extern volatile u32 *volatile D_800B8BA0;
extern char D_800C5AB4;
extern void func_8009C938(void *message);

static __inline__ u32 read_busy_loop(void) {
    register volatile u32 *status asm("$2");
    asm volatile("lw %0,D_800B8B80" : "=r"(status));
    return *status;
}

s32 func_8009C88C(void) {
    volatile s32 counter;
    s32 remaining;
    register volatile u32 *status asm("$3");
    register s32 initial_counter asm("$2");

    asm("lw %0,D_800B8B80" : "=r"(status));
    asm("lui %0,0x10" : "=r"(initial_counter) : "r"(status));
    counter = initial_counter;
    if (*status & 0x01000000) {
        register s32 sentinel asm("$4") = -1;
        do {
            remaining = counter - 1;
            counter = remaining;
            remaining = counter;
            if (remaining == sentinel) {
                register char *message asm("$4");
                asm("lui %0,0x800C" : "=r"(message));
                message += 0x5AB4;
                func_8009C938(message);
                return -1;
            }
        } while (read_busy_loop() & 0x01000000);
    }
    return 0;
}

u32 func_8009C920(void) {
    register volatile u32 *status asm("$2");
    asm volatile("lw %0,D_800B8BA0" : "=r"(status));
    return *status;
}

extern volatile int D_800B6C74;
extern unsigned char D_800C4DB8;
extern void func_80096F9C(void *message, int scale);
extern void func_80096FFC(int value);
extern void func_8009700C(int command, int value);

void func_800889E8(int target, int scale) {
    register int scaled asm("$5") = scale << 15;
    register int current asm("$2");
    volatile int counter = scaled;

    asm("" : "+r"(scaled));
    asm volatile("" : : "m"(counter) : "memory");
    current = D_800B6C74;
    if (current < target) {
        register int sentinel asm("$3") = -1;

        do {
            counter--;
            if (counter == sentinel) {
                register void *message asm("$4");

                asm volatile("lui %0,0x800C"
                             : "=r"(message));
                message = (unsigned char *)message + 0x4DB8;
                func_80096F9C(message, scaled);
                func_80096FFC(0);
                func_8009700C(3, 0);
                return;
            }
            asm volatile("lui $2,%%hi(D_800B6C74)\n\t"
                         "lw $2,%%lo(D_800B6C74)($2)\n\t"
                         "nop"
                         : "=r"(current) : : "memory");
        } while (current < target);
    }
}

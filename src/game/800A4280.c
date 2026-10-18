extern unsigned int D_800A40E4[];
extern unsigned int D_800A4154[];

void func_800A4280(void) {
    register unsigned int *destination asm("$2") = (unsigned int *)0xDF80;
    register unsigned int *source asm("$10") = D_800A40E4;
    register unsigned int *end asm("$9") = D_800A4154;

    asm("" : "+r"(destination), "+r"(source), "+r"(end));
    do {
        unsigned int value = *source;

        asm volatile("" : "+r"(value) : : "memory");
        *destination++ = value;
        source++;
    } while (source != end);
}

void func_800A3168(void);
void func_800A3954(void);
void D_800A3318(void);

void func_800A3134(void) {
    register unsigned int value asm("$2") = (unsigned int)func_800A3168;
    register unsigned int *destination asm("$1") = (unsigned int *)0x800C0000;

    asm("" : "+r"(value), "+r"(destination));
    destination[-0x7374 / 4] = value;
    asm("" : : : "memory");
    {
        register unsigned int next_value asm("$2") = (unsigned int)func_800A3954;
        register unsigned int *next_destination asm("$1") = (unsigned int *)0x800C0000;

        asm("" : "+r"(next_value), "+r"(next_destination));
        next_destination[-0x7370 / 4] = next_value;
    }
    asm("" : : : "memory");
    {
        register unsigned int last_value asm("$2") = (unsigned int)D_800A3318;
        register unsigned int *last_destination asm("$1") = (unsigned int *)0x800C0000;

        asm("" : "+r"(last_value), "+r"(last_destination));
        last_destination[-0x736C / 4] = last_value;
    }
}

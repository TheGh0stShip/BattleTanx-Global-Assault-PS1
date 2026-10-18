extern unsigned char D_800EDF08[];
extern int func_80083A5C(unsigned int index);

void func_80083B2C(unsigned int index) {
    if (index < 4) {
        register unsigned char *base asm("$2") = D_800EDF08;
        unsigned char *entry;

        asm("" : "+r"(base));
        entry = (unsigned char *)(index * 20 + (unsigned int)base);

        if (*(unsigned int *)entry == 0) {
            int value = func_80083A5C(index);

            while (func_80083A5C(index) == value) {
            }
        }
    }
}

typedef struct Entry {
    unsigned int state;
    unsigned char rest[28];
} Entry;

extern Entry * volatile D_800EF230;

void func_800A2FB0(unsigned int first, unsigned int count) {
    register unsigned int index asm("$6");

    if (count != 0) {
        index = 0;
        do {
            register unsigned int offset asm("$2") = index + first;
            register Entry *entries asm("$3");
            register Entry **globals asm("$3");

            asm("" : "+r"(offset));
            index++;
            asm volatile("" ::: "memory");
            globals = (Entry **)0x800F0000;
            asm("" : "+r"(globals));
            entries = globals[-884];
            asm("" : "+r"(entries));
            offset <<= 5;
            entries = (Entry *)((unsigned char *)entries + offset);
            asm("" : "+r"(entries));
            entries->state = 0;
        } while (index < count);
    }
}

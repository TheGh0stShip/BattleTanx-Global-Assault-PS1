extern unsigned char D_800EE488[];
extern void func_80086308(int index, void *argument);
extern void func_8008523C(int index, unsigned int first, unsigned int second);

void func_800863D8(unsigned int amount) {
    unsigned int index;
    register unsigned char *entry asm("$17");

    if (amount != 0) {
        index = 0;
        asm("lui $2,%%hi(D_800EE488)\n\taddiu $17,$2,%%lo(D_800EE488)"
            : "=r"(entry) : : "$2");
        do {
            unsigned char *record = *(unsigned char **)(entry + 0x10);

            if (record != 0) {
                unsigned int elapsed = *(unsigned int *)(entry + 0x08) + amount;

                if (elapsed >= *(unsigned short *)(record + 0x02)) {
                    record += 4;
                    if (*(unsigned short *)(record + 0x02) == 0) {
                        func_80086308(index, (void *)1);
                        func_8008523C(index, 0, 0);
                        record = 0;
                    } else {
                        func_8008523C(index, record[0], record[1]);
                    }
                    *(unsigned char **)(entry + 0x10) = record;
                    elapsed = 0;
                }
                *(unsigned int *)(entry + 0x08) = elapsed;
            }
            index++;
            entry += 0x10;
        } while (index < 8);
    }
}

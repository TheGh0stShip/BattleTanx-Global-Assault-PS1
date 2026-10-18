struct MaskValue {
    unsigned short mask;
    unsigned short value;
};

extern unsigned char D_800EDF78[];

unsigned int func_80084034(unsigned int index, unsigned int enabled) {
    register unsigned char *base asm("$2") = D_800EDF78;
    unsigned char *slot;
    register struct MaskValue *entry asm("$2");
    struct MaskValue *cursor;
    unsigned int result;
    unsigned int mask;

    asm("" : "+r"(base));
    index *= 4;
    slot = (unsigned char *)(index + (unsigned int)base);
    entry = *(struct MaskValue **)(slot + 0x2C);
    mask = entry->mask;
    result = 0;
    if (mask != 0) {
        cursor = entry;
        do {
            if ((mask & enabled) == mask) {
                result |= cursor->value;
            }
            cursor++;
            mask = cursor->mask;
        } while (mask != 0);
    }
    return result & 0xFFFF;
}

typedef signed int s32;
typedef signed short s16;

extern s16 D_800A5DA8[];

s32 func_80053354(s32 value) {
    register s32 shifted asm("$6");
    register s32 table asm("$5");
    register s32 next_or_base asm("$2");
    register s32 sum asm("$3");
    register s32 low_bits asm("$4");

    value += 0x1000;
    shifted = value >> 1;
    asm volatile("" : "+r"(shifted), "+r"(value));
    value >>= 5;
    value &= 0xFF;
    table = (s32)D_800A5DA8;
    asm volatile("" : "+r"(table), "+r"(value));
    next_or_base = value + 1;
    next_or_base = (next_or_base << 1) + table;
    asm volatile("" : "+r"(next_or_base));
    value <<= 1;
    asm volatile("" : "+r"(value));
    value += table;
    sum = *(s16 *)next_or_base;
    next_or_base = *(s16 *)value;
    shifted &= 0xF;
    sum -= next_or_base;
    asm volatile(
        ".set noreorder\n\t"
        "mult $6,$3\n\t"
        "sll $3,$3,2\n\t"
        "andi $3,$3,7\n\t"
        "mflo $6");
    asm volatile("" : "+r"(shifted), "+r"(sum));
    low_bits = (shifted >> 2) & 3;
    shifted = low_bits | sum;
    return shifted + next_or_base;
}

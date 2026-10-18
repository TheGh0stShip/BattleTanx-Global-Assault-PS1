unsigned int func_8009EF74(const unsigned char *state) {
    register int first asm("$2") = state[227];
    register int second asm("$5") = state[233];
    register unsigned int base asm("$4") =
        *(const unsigned int *)(state + 236);
    register int second_bytes asm("$3");

    asm("" : "+r"(first), "+r"(second), "+r"(base));
    first++;
    first >>= 1;
    first <<= 2;

    second_bytes = second << 2;
    second_bytes += second;
    second_bytes += 3;
    second_bytes &= 0xFFC;
    second_bytes += 4;
    first += second_bytes;
    asm("" : "+r"(first), "+r"(second_bytes), "+r"(base));
    return first + base;
}

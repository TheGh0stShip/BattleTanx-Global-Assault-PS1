extern unsigned int D_800EE488;

int func_800862D4(int index) {
    register unsigned int result asm("$2");
    register unsigned int mask asm("$3") = 1;

    if (index != -1) {
        asm("");
        result = D_800EE488;
        mask <<= index;
        asm("" : "+r"(mask));
        result &= mask;
        return result != 0;
    }
    result = D_800EE488;
    return result != 0;
}

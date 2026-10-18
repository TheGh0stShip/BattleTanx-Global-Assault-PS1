int func_80052E54(const unsigned char *object) {
    register unsigned int upper asm("$3") = object[0xBD];
    register unsigned int lower asm("$2");

    asm("" : "+r"(upper));
    lower = object[0x85];
    asm("" : "+r"(lower));
    return lower < upper;
}

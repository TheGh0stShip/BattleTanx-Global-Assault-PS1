int func_80047B28(unsigned int first, unsigned int second,
                  unsigned short *distance) {
    register unsigned int first16 asm("$3") = (unsigned short)first;
    register unsigned int second16 asm("$2") = (unsigned short)second;
    int direction;

    asm("" : "+r"(first16), "+r"(second16));
    if (second16 < first16) {
        first -= second;
        direction = -1;
    } else {
        first = second - first;
        direction = 1;
    }
    if ((unsigned short)first > 0x8000) {
        first = ~first;
        direction = -direction;
    }
    *distance = first;
    return (short)direction;
}

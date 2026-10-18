unsigned int func_80047B98(int first, int second) {
    register int difference asm("$2") = second - first;

    asm("" : "+r"(difference));
    difference = (short)difference;
    asm("" : "+r"(difference));
    if (difference < 0) {
        difference = -difference;
    }
    return (unsigned short)difference;
}

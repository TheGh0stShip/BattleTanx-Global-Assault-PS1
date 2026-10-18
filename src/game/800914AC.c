typedef unsigned short u16;

int func_800914AC(u16 index) {
    register int offset asm("$3") = index;
    register int result asm("$2");
    register unsigned char *base asm("$2");

    asm("" : "+r"(offset));
    result = offset < 3;
    asm("" : "+r"(result));
    offset <<= 4;
    if (result == 0) {
        goto zero;
    }
    base = (unsigned char *)0x800B0000;
    asm("" : "+r"(base));
    base = *(unsigned char **)(base + 0x5940);
    asm("" : "+r"(base));
    asm("addu $3,$3,$2" : "+r"(offset) : "r"(base));
    result = *(u16 *)(unsigned long)offset;
    goto done;

zero:
    asm("addu $2,$0,$0" : "=r"(result));
done:
    asm("");
    return result;
}

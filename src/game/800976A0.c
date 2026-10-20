int func_800976A0(volatile unsigned char *digits) {
    register unsigned int x asm("$3") = digits[0];
    register unsigned int y asm("$6") = digits[1];
    register unsigned int value asm("$2");
    register unsigned int total asm("$5");
    register unsigned int high asm("$4");

    total = x >> 4;
    value = (total << 2) + total;
    value <<= 1;
    x &= 15;
    value += x;
    total = (value << 4) - value;
    total <<= 2;
    x = y >> 4;
    value = (x << 2) + x;
    value <<= 1;
    y &= 15;
    value += y;
    total += value;
    x = (total << 2) + total;
    value = x << 4;
    total = digits[2];
    value -= x;
    high = total >> 4;
    x = (high << 2) + high;
    x <<= 1;
    total &= 15;
    x += total;
    value += x;
    return value - 150;
}

unsigned int func_80047AC8(unsigned short *current, unsigned int target,
                           unsigned int step) {
    register unsigned int current_value asm("$7") = *current;
    register unsigned int difference asm("$3") = target - current_value;
    register int signed_difference asm("$2") = (short)difference;
    register unsigned int magnitude asm("$9");
    register unsigned int direction asm("$8");
    register unsigned int result asm("$2");
    register int movement asm("$2");
    register unsigned int magnitude16 asm("$2");
    register unsigned int step16 asm("$3");

    asm("" : "+r"(current_value), "+r"(difference),
        "+r"(signed_difference));
    magnitude = signed_difference;
    if (signed_difference < 0) {
        magnitude = -magnitude;
    }
    asm("" : "+r"(magnitude));
    direction = (unsigned short)difference;
    magnitude16 = (unsigned short)magnitude;
    step16 = (unsigned short)step;
    asm("" : "+r"(direction), "+r"(magnitude16), "+r"(step16));
    result = magnitude16 < step16;
    if (result != 0) {
        *current = target;
    } else {
        movement = direction << 16;
        if (movement < 0) {
            result = current_value - step;
        } else {
            result = current_value + step;
        }
        *current = result;
    }
    return (unsigned short)magnitude;
}

int func_800861DC(const unsigned char *left, const unsigned char *right) {
    register unsigned int left_value asm("$2");
    register unsigned int right_value asm("$3");

again:
    left_value = *left;
    right_value = *right;
    asm("" : "+r"(left_value), "+r"(right_value));
    if (left_value == 0) {
        left++;
        goto done;
    }
    left++;
    left_value ^= right_value;
    asm("" : "+r"(left_value));
    left_value = left_value != 0;
    asm("" : "+r"(left_value));
    if (left_value == 0) {
        right++;
        goto again;
    }
done:
    return left_value ^ 1;
}

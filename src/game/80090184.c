int func_80090184(const char *text) {
    register int result asm("$2");
    register int length asm("$3") = 0;

    asm("" : "+r"(length));
    if (text == 0) {
        result = 0;
        goto done;
    }
    asm("");
    goto test;

increment:
    length++;
test:
    result = *(const signed char *)text;
    asm("" : "+r"(result));
    text++;
    if (result != 0) {
        goto increment;
    }
    result = length;
done:
    asm("");
    return result;
}

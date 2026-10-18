int func_8008B830(int value) {
    register int result asm("$2");

    if (value >= 0) {
        result = value;
        goto done;
    }
    result = value;
    asm("" : "+r"(result));
    result = -result;
done:
    return result;
}

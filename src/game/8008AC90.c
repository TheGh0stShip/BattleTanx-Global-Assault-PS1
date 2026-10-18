void *func_8008AC90(unsigned char *destination, int count) {
    register unsigned char *result asm("$2");

    if (destination == 0) {
        result = 0;
        goto done;
    }
    result = destination;
    if (count > 0) {
        goto fill;
    }
    result = 0;
    goto done;

fill:
    do {
        *destination = 0;
        count--;
        destination++;
    } while (count > 0);

done:
    asm("");
    return result;
}

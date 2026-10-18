unsigned char *func_8008DA04(
    unsigned char *destination,
    const unsigned char *source
) {
    register unsigned char *result asm("$3");
    unsigned int value = 0;

    if (destination != 0) {
        if (source != 0) {
            result = destination;
            asm("" : "+r"(result));
            value = *source++;
            destination = result + 1;
            *result = value;
            if (value != 0) {
                do {
                    value = *source++;
                    *destination++ = value;
                } while (value != 0);
            }
            value = (unsigned int)result;
        }
    }
    return (unsigned char *)value;
}

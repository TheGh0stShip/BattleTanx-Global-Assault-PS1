char *func_80094044(char *destination, char *source, int count) {
    char *result;
    char *start;
    int index;
    unsigned int character;

    if (destination == 0) {
        goto null_result;
    }
    index = 0;
    if (source == 0) {
        goto null_result;
    }
    start = destination;
    if (count > 0) {
        do {
            character = *source++;
            *destination++ = character;
            if (character == 0) {
                index++;
                goto fill_test;
            fill:
                asm volatile("");
                *destination++ = 0;
                index++;
            fill_test:
                if (index < count) {
                    goto fill;
                }
                goto done;
            }
        } while (++index < count);
    }
done:
    result = start;
    goto end;
null_result:
    result = 0;
end:
    asm volatile("" : "+r"(result));
    return result;
}

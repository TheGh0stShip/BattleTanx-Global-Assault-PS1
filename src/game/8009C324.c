void func_8009C324(unsigned int *destination, unsigned int *source, unsigned int count) {
    unsigned int index;
    for (index = 0; index < count; index++) {
        *destination++ = *source++;
    }
}

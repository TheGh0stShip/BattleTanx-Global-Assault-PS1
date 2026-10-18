extern unsigned char D_800EE588[];

void *func_80087664(void) {
    unsigned char *state = D_800EE588;
    register int index asm("$4") = *(int *)(state + 0x55C);
    register void *result asm("$3") = 0;

    if (index < *(int *)(state + 0x558)) {
        register int temporary asm("$2") = index * 40;

        result = state + 0x300;
        asm("" : "+r"(result));
        result = (void *)(temporary + (unsigned int)result);
        temporary = index + 1;
        *(int *)(state + 0x55C) = temporary;
    }
    return result;
}

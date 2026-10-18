extern void func_800149B8(void *value);

void func_80052A60(unsigned char *object) {
    register unsigned char *cursor asm("$4") = object;

    asm("" : "+r"(cursor));
    cursor[0x64] = 0;
    cursor = *(unsigned char **)(cursor + 0x5C);
    asm("" : "+r"(cursor));
    func_800149B8(cursor);
}

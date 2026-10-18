extern int D_800EAFBC;
extern unsigned char *func_8005A2A0(void *object);
extern void func_8005A2F0(void *first, void *second);

int func_8005F700(unsigned char *object) {
    unsigned char *entry = func_8005A2A0(object);
    unsigned char *last = *(unsigned char **)(object + 4) + 0xA0;
    if (entry != last) {
        func_8005A2F0(entry, last);
        entry[1] = 0x10;
    }
    D_800EAFBC = 2;
    return 1;
}

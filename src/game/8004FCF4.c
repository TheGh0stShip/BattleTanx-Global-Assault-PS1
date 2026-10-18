extern void func_8004DD5C(unsigned char *object);
extern void func_8004D804(unsigned char *object);

void func_8004FCF4(unsigned char *object) {
    *(unsigned int *)(object + 0x184) = 0;
    *(unsigned int *)(object + 0x218) &= ~0x100U;
    func_8004DD5C(object);
    func_8004D804(object);
}

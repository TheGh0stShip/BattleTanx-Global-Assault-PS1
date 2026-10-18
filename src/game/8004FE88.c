void func_8004DD5C(unsigned char *object);
void func_8004D804(unsigned char *object);

void func_8004FE88(unsigned char *object, int value) {
    *(int *)(object + 0x184) = 1;
    *(int *)(object + 0x188) = value;
    *(unsigned int *)(object + 0x218) &= ~0x100U;
    func_8004DD5C(object);
    func_8004D804(object);
}

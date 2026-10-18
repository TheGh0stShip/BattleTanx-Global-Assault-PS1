void func_8004E0BC(unsigned char *object);
void func_8004D804(unsigned char *object);

void func_8004FFE0(unsigned char *object) {
    *(int *)(object + 0x184) = 1;
    *(unsigned int *)(object + 0x218) &= ~0x100U;
    func_8004E0BC(object);
    func_8004D804(object);
}

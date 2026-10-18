void func_8004E0BC(unsigned char *object);
void func_8004D7D8(unsigned char *object);

void func_8004FDD4(unsigned char *object, int first, int second) {
    *(int *)(object + 0x184) = first;
    *(int *)(object + 0x188) = second;
    *(unsigned int *)(object + 0x218) &= ~0x100U;
    func_8004E0BC(object);
    func_8004D7D8(object);
}

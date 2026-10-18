extern void func_8004E0BC(unsigned char *object);
extern void func_8004D7D8(unsigned char *object);

void func_8004FC20(unsigned char *object) {
    *(unsigned int *)(object + 0x218) &= ~0x100U;
    func_8004E0BC(object);
    func_8004D7D8(object);
}

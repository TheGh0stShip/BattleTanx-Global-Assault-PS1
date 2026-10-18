extern void func_80069494(int object, void *position, int zero,
                         unsigned short value, int final, unsigned char extra);

void func_80034020(unsigned char *object) {
    func_80069494(*(int *)(object + 0x1C), object + 8, 0,
                  *(unsigned short *)(object + 0x14), 0, object[0x19]);
}

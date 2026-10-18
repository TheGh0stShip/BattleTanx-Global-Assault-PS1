extern void func_8006A1BC(int object, void *position, int zero,
                         unsigned short value, int final);

void func_800371BC(unsigned char *object) {
    if (*(unsigned int *)(object + 0x1C) >= 2) {
        func_8006A1BC(*(int *)(object + 0x18), object + 8, 0,
                      *(unsigned short *)(object + 0x14), 0);
    }
}

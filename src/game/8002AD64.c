extern void func_8006A1BC(int object, void *position, unsigned short first,
                         unsigned short second, int final);

void func_8002AD64(unsigned char *object) {
    if (object[0x37] == 2) {
        func_8006A1BC(*(int *)(object + 0x10), object + 0x24,
                      *(unsigned short *)(object + 0x34),
                      *(unsigned short *)(object + 0x32), 0);
    }
}

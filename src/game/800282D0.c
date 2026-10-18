extern int D_800A44CC[];
extern void func_8006A158(int type, void *position, int zero, unsigned short value, int final);

void func_800282D0(unsigned char *object) {
    func_8006A158(D_800A44CC[*(int *)(object + 0x18)], object + 8, 0,
                 *(unsigned short *)(object + 0x14), 0);
}

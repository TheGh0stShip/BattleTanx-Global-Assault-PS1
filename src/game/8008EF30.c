extern unsigned char D_800EEDE4[];
extern void func_8008AA48(void *destination, int value, int size);

void func_8008EF30(void) {
    func_8008AA48(D_800EEDE4, 0, 0x10);
}

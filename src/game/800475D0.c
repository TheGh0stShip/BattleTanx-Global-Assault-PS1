extern unsigned char D_800DE33C[];
extern short D_800DE338;
extern void func_8008AA48(void *destination, int value, int size);

void func_800475D0(void) {
    func_8008AA48(D_800DE33C, 0, 0x5980);
    D_800DE338 = 0;
}

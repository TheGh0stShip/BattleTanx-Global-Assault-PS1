extern int D_800EC334[];

void func_8008AA48(void *destination, int value, int size);

void func_8007F640(void) {
    func_8008AA48(D_800EC334, 0, 0x18);
    D_800EC334[4] = 0x19000;
    D_800EC334[5] = 2;
}

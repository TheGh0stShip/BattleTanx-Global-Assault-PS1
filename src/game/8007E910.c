extern unsigned char D_800EC200[];
extern int D_80086058;

void func_8008AA48(void *destination, int value, unsigned int size);
int func_80094288(void);

void func_8007E910(void) {
    func_8008AA48(D_800EC200, 0, 0x134);
    *(unsigned int *)(D_800EC200 + 0x108) = 0;
    if (D_80086058 != 0 && func_80094288() != 0) {
        D_80086058 = 0;
    }
}

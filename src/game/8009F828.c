void func_80094198(void);
void func_800A42B4(void);
void func_80094168(void);

void func_8009F828(void) {
    func_80094198();
    func_800A42B4();
    asm volatile(
        ".word 0x0C025BFF\n\t"
        ".word 0x00002021"
        :
        :
        : "$4", "$31", "memory"
    );
    func_80094168();
}

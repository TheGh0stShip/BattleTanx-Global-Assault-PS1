void func_80094198(void);
void func_800A42B4(void);
void func_80096FFC(int value);
void func_80094168(void);

void func_8009F828(void) {
    func_80094198();
    func_800A42B4();
    asm volatile(
        ".set noreorder\n\t"
        "jal func_80096FFC\n\t"
        "addu $4,$zero,$zero\n\t"
        ".set reorder"
        :
        :
        : "$4", "$31", "memory"
    );
    func_80094168();
}

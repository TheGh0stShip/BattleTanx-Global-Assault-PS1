extern void func_8009F89C(int value);
extern void func_8009F998(void);

void func_80096F9C(unsigned char *values) {
    register int value asm("$4");

    if (values == 0) {
        asm("lui $16,0x800C" : "=r"(values));
        values += 0x54C8;
    }
    while ((value = *values++ << 24) != 0) {
        func_8009F89C(value >> 24);
    }
    func_8009F998();
}

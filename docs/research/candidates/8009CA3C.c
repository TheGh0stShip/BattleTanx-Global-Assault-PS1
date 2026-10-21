extern int D_800EFD08;
extern void func_8009713C(int command, void *data, int value);
extern void func_80097128(void (*callback)(void));
extern void func_80097558(void (*callback)(void));
extern void func_800A2FF0(void);
extern void func_8009BA08(void);

void func_8009CAC0(void);

void func_8009CA3C(int flags) {
    unsigned char command = (unsigned char)flags;

    func_8009713C(0xE, &command, 0);
    if ((flags & 0x100) != 0) {
        register int enabled asm("$2") = 1;

        if ((flags & 0x20) != 0) {
            asm volatile("lui $1,%%hi(D_800EFD08)\n\t"
                         "j 1f\n\t"
                         "sw $0,%%lo(D_800EFD08)($1)\n"
                         "1:"
                         : : : "$1", "memory");
        } else {
            asm volatile("lui $1,%%hi(D_800EFD08)\n\t"
                         "sw %0,%%lo(D_800EFD08)($1)"
                         : : "r"(enabled) : "$1", "memory");
        }
        func_80097558(func_800A2FF0);
        func_80097128(func_8009CAC0);
    }
    func_8009713C(0x1B, 0, 0);
}

void func_8009CAC0(void) {
    func_8009BA08();
}

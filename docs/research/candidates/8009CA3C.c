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
        register int condition asm("$2") = flags & 0x20;

        if (condition != 0) {
            register int *destination asm("$1");
            asm("lui %0,0x800F" : "=r"(destination));
            *(int *)((char *)destination - 0x2F8) = 0;
        } else {
            register int *destination asm("$1");
            condition = 1;
            asm("lui %0,0x800F" : "=r"(destination));
            *(int *)((char *)destination - 0x2F8) = condition;
        }
        {
            register char *callback asm("$4");
            asm("lui %0,0x800A" : "=r"(callback));
            callback += 0x2FF0;
            func_80097558((void (*)(void))callback);
        }
        {
            register char *callback asm("$4");
            asm("lui %0,0x800A" : "=r"(callback));
            callback -= 0x3540;
            func_80097128((void (*)(void))callback);
        }
    }
    func_8009713C(0x1B, 0, 0);
}

void func_8009CAC0(void) {
    func_8009BA08();
}

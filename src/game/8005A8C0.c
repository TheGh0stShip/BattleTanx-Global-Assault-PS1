extern volatile unsigned int D_800C60D0;

unsigned int func_800229F8(void);
void func_80059BB8(void);
void func_80059DB4(void);
void func_800633C0(void);
void func_80059EAC(void);

void func_8005A8C0(void) {
    register unsigned int value asm("$3");

    if ((func_800229F8() & 0xFF) == 0) {
        func_80059BB8();
    }
    func_80059DB4();
    func_800633C0();
    value = D_800C60D0;
    asm("" : "+r"(value));
    func_80059EAC();
}

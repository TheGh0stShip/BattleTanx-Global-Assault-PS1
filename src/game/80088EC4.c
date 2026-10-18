struct StreamInitState {
    unsigned char pad_00[0x30];
    unsigned char ready_30;
    unsigned char pad_31;
    unsigned char active_32;
    unsigned char active_33;
    unsigned char pad_34[0x18];
    unsigned int size_4C;
};

extern struct StreamInitState D_800EEAE8;

void func_8008AA48(void *destination, int value, unsigned int size);
void func_8009196C(void (*callback)(void));
int func_80091804(void);
void func_80089120(void);

void func_80088EC4(void) {
    func_8008AA48(&D_800EEAE8, 0, 0xA8);
    func_8009196C(func_80089120);
    D_800EEAE8.size_4C = 0x4000;
    D_800EEAE8.active_32 = 1;
    D_800EEAE8.active_33 = 1;
    asm("" ::: "memory");
    if (func_80091804() != 0) {
        asm("" ::: "memory");
        D_800EEAE8.ready_30 = 1;
    }
}

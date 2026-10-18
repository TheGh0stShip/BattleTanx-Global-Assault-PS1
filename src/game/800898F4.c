typedef unsigned char u8;

typedef struct RuntimeState {
    u8 unknown_00[0x3A];
    u8 transition_pending;
    u8 transition_started;
} RuntimeState;

extern RuntimeState D_800EEAE8;
extern void func_80089858(void);
extern void func_8009162C(void (*callback)(void));
extern void func_80091604(int value);
extern int func_80089098(int value);
extern void func_80089A58(void);
extern void func_80088E48(u8 mode);

void func_800898F4(unsigned int mode)
{
    mode &= 0xFF;
    if (mode == 2) {
        func_8009162C(func_80089858);
        func_80091604(0);
        return;
    }

    if (D_800EEAE8.transition_pending != 0) {
        D_800EEAE8.transition_started = 1;
        asm volatile("" ::: "memory");
        return;
    }

    if (func_80089098(1) != 0) {
        func_80089A58();
        return;
    }
    func_80088E48(mode);
}

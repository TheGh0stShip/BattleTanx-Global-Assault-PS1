typedef struct {
    unsigned short active;
    char pad[0x30];
    unsigned short saved_mask;
    unsigned int saved_mode;
} SpuSaveState;

extern SpuSaveState D_800B5A78;
extern volatile unsigned short *D_800B6B08;
extern volatile unsigned short *D_800B6B04;
extern volatile unsigned int *D_800B6B0C;
extern void func_80094198(void);
extern void func_8009DA68(void);

SpuSaveState *func_800948FC(void)
{
    SpuSaveState *s;
    volatile unsigned short *mask;
    volatile unsigned short *out;

    s = &D_800B5A78;
    __asm__("" : "=r"(s) : "0"(s));
    if (s->active == 0) {
        return 0;
    }
    func_80094198();
    mask = D_800B6B08;
    s->saved_mask = *mask;
    out = D_800B6B04;
    s->saved_mode = *D_800B6B0C;
    *mask = 0;
    *out = *mask;
    *D_800B6B0C &= 0x77777777;
    func_8009DA68();
    s->active = 0;
    return s;
}

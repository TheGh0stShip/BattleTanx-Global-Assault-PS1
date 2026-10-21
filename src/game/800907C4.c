typedef struct {
    char pad[0x188];
    unsigned short key_on[2];
    unsigned short key_off[2];
} SpuRegs;

extern volatile int D_800B7BBC;
extern volatile unsigned int D_800B7788;
extern volatile unsigned int D_800B7784;
extern volatile unsigned int D_800B775C;
extern SpuRegs *D_800B76F0;
extern volatile unsigned short D_800EF188[4];

void func_800907C4(int on_off, unsigned int voice_bit) {
    unsigned int high;
    volatile unsigned short *req;

    voice_bit &= 0xFFFFFF;
    high = voice_bit >> 16;
    switch (on_off) {
    case 1:
        if (D_800B7BBC & 1) {
            req = D_800EF188;
            __asm__("" : "=r"(req) : "0"(req));
            req[0] = voice_bit;
            req[1] = high;
            D_800B7788 |= 1;
            D_800B7784 |= voice_bit;
            if (req[2] & voice_bit) {
                req[2] &= ~voice_bit;
            }
            if (req[3] & high) {
                req[3] &= ~high;
            }
        } else {
            D_800B76F0->key_on[0] = voice_bit;
            D_800B76F0->key_on[1] = high;
            D_800B775C |= voice_bit;
        }
        break;
    case 0:
        if (D_800B7BBC & 1) {
            req = D_800EF188;
            __asm__("" : "=r"(req) : "0"(req));
            req[2] = voice_bit;
            req[3] = high;
            D_800B7788 |= 1;
            D_800B7784 &= ~voice_bit;
            if (req[0] & voice_bit) {
                req[0] &= ~voice_bit;
            }
            if (req[1] & high) {
                req[1] &= ~high;
            }
        } else {
            D_800B76F0->key_off[0] = voice_bit;
            D_800B76F0->key_off[1] = high;
            D_800B775C &= ~voice_bit;
        }
        break;
    }
}

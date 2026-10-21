typedef void (*DmaHandler)(void);

extern DmaHandler D_800B8C30[8];
extern volatile unsigned int *D_800B8C2C;
extern volatile int *D_800B8C50;
extern char D_800C5CF8[];
extern char D_800C5D14[];
extern void func_8009DA10(void *, int);
extern void func_80094420(int, void (*)(void));
extern void func_800943B0(char *, ...);

void func_8009D7E4(void);
DmaHandler func_8009D964(int channel, DmaHandler handler);

void *func_8009D798(void)
{
    func_8009DA10(D_800B8C30, 8);
    *D_800B8C2C = 0;
    func_80094420(3, func_8009D7E4);
    return func_8009D964;
}

void func_8009D7E4(void)
{
    unsigned int mask;
    int i;

    while ((mask = (*D_800B8C2C >> 24) & 0x7F) != 0) {
        for (i = 0; mask != 0 && i < 7; i++, mask >>= 1) {
            if (mask & 1) {
                *D_800B8C2C &= (1 << (i + 24)) | 0xFFFFFF;
                if (D_800B8C30[i] != 0) {
                    D_800B8C30[i]();
                }
            }
        }
    }
    if ((*D_800B8C2C & 0xFF000000) == 0x80000000 || (*D_800B8C2C & 0x8000)) {
        func_800943B0(D_800C5CF8, *D_800B8C2C);
        for (i = 0; i < 7; i++) {
            func_800943B0(D_800C5D14, i, D_800B8C50[i * 4]);
        }
    }
}

static inline DmaHandler keep(DmaHandler h)
{
    __asm__("" : "=r"(h) : "0"(h));
    return h;
}

DmaHandler func_8009D964(channel, handler)
    int channel;
    DmaHandler handler;
{
    DmaHandler old = D_800B8C30[channel];

    if (handler == old) {
        return old;
    }
    if (handler != 0) {
        D_800B8C30[channel] = handler;
        *D_800B8C2C = (*D_800B8C2C & 0xFFFFFF) | 0x800000 | (1 << (channel + 16));
    } else {
        D_800B8C30[channel] = 0;
        *D_800B8C2C = ((*D_800B8C2C & 0xFFFFFF) | 0x800000) & ~(1 << (channel + 16));
    }
    return keep(old);
}

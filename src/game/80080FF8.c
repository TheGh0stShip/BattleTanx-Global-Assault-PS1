typedef struct {
    short x;
    short y;
    short w;
    short h;
} RECT;

typedef struct {
    short w;
    short h;
} Size;

extern Size D_800B0C64;
extern unsigned long *D_800B0D34;
extern unsigned long *D_800B0D38;
extern unsigned long *D_800B0D3C;
extern unsigned long *D_800B0D40;
extern unsigned long *D_800B0D44;
extern void func_80081B28(void);
extern int func_80081B5C(void);

int func_80080FF8(RECT *r, unsigned long *q) {
    register unsigned long *p asm("$18");
    register RECT *rect asm("$17");
    int size;
    int n;
    int d;

    rect = r;
    __asm__("" : "+r"(rect));
    p = q;
    func_80081B28();
    rect->w = rect->w < 0 ? 0 : (D_800B0C64.w < rect->w ? D_800B0C64.w : rect->w);
    rect->h = rect->h < 0 ? 0 : (D_800B0C64.h < rect->h ? D_800B0C64.h : rect->h);
    size = (rect->w * rect->h + 1) / 2;
    if (size <= 0) {
        return -1;
    }
    d = size % 16;
    n = size / 16;
    if ((*D_800B0D38 & 0x04000000) == 0) {
        __asm__ volatile("" : : : "$3");
        do {
            if (func_80081B5C() != 0) {
                return -1;
            }
        } while ((*D_800B0D38 & 0x04000000) == 0);
    }
    *D_800B0D38 = 0x04000000;
    *D_800B0D34 = 0x01000000;
    *D_800B0D34 = 0xC0000000;
    *D_800B0D34 = ((unsigned long *)rect)[0];
    *D_800B0D34 = ((unsigned long *)rect)[1];
    if ((*D_800B0D38 & 0x08000000) == 0) {
        __asm__ volatile("" : : : "$3");
        do {
            if (func_80081B5C() != 0) {
                return -1;
            }
        } while ((*D_800B0D38 & 0x08000000) == 0);
    }
    for (d--; d != -1; d--) {
        *p++ = *D_800B0D34;
    }
    if (n != 0) {
        *D_800B0D38 = 0x04000003;
        *D_800B0D3C = (unsigned long)p;
        *D_800B0D40 = (n << 16) | 0x10;
        *D_800B0D44 = 0x01000200;
    }
    return 0;
}

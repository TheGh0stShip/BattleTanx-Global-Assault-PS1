typedef struct {
    short x;
    short y;
    short w;
    short h;
} RECT;

extern short D_800B0C64;
extern short D_800B0C66;
extern unsigned long *D_800B0D38;
extern unsigned long D_800EC34C[];
extern unsigned long D_800EC374[];

extern unsigned long func_80081338(int);
extern void func_800812F0(unsigned long *);

int func_80080B8C(RECT *rect, unsigned long color)
{
    rect->w = (rect->w < 0) ? 0 : (rect->w > D_800B0C64 - 1) ? D_800B0C64 - 1 : rect->w;
    rect->h = (rect->h < 0) ? 0 : (rect->h > D_800B0C66 - 1) ? D_800B0C66 - 1 : rect->h;
    if ((rect->x & 0x3F) || (rect->w & 0x3F)) {
        D_800EC34C[0] = ((unsigned long)D_800EC374 & 0xFFFFFF) | 0x08000000;
        D_800EC34C[1] = 0xE3000000;
        D_800EC34C[2] = 0xE4FFFFFF;
        D_800EC34C[3] = 0xE5000000;
        D_800EC34C[4] = 0xE6000000;
        D_800EC34C[5] = 0xE1000000 | (*D_800B0D38 & 0x7FF) | ((color >> 31) << 10);
        D_800EC34C[6] = 0x60000000 | (color & 0xFFFFFF);
        D_800EC34C[7] = *(unsigned long *)&rect->x;
        D_800EC34C[8] = *(unsigned long *)&rect->w;
        D_800EC374[0] = 0x03FFFFFF;
        D_800EC374[1] = 0xE3000000 | func_80081338(3);
        D_800EC374[2] = 0xE4000000 | func_80081338(4);
        D_800EC374[3] = 0xE5000000 | func_80081338(5);
    } else {
        D_800EC34C[0] = 0x05FFFFFF;
        D_800EC34C[1] = 0xE6000000;
        D_800EC34C[2] = 0xE1000000 | (*D_800B0D38 & 0x7FF) | ((color >> 31) << 10);
        D_800EC34C[3] = 0x02000000 | (color & 0xFFFFFF);
        D_800EC34C[4] = *(unsigned long *)&rect->x;
        D_800EC34C[5] = *(unsigned long *)&rect->w;
    }
    {
        int r = 0;

        func_800812F0(D_800EC34C);
        __asm__ volatile("" : "+r"(r));
        return r;
    }
}

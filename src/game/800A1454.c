typedef struct {
    int pad0[2];
    int addr;
    int pad0C;
    int step;
    int remaining;
    int pad18[2];
    int blocks;
    int dma_a;
    int dma_b;
    int irq;
    int flags;
    int arg;
} XferState;

extern XferState D_800B90BC;
extern void (*D_800B90B8)(int, int);
extern void func_80097114(int);
extern void func_80097128(int);
extern void func_80097558(int);
extern void func_80097278(int, int);

void func_800A1454(void)
{
    volatile XferState *s;

    s = &D_800B90BC;
    s->addr += s->step * 4;
    s->remaining--;
    s->blocks++;
    if (s->remaining == 0) {
        func_80097114(s->dma_a);
        func_80097128(s->dma_b);
        if (s->flags & 1) {
            func_80097558(s->irq);
        }
        func_80097278(9, 0);
        if (D_800B90B8 != 0) {
            D_800B90B8(2, s->arg);
        }
    }
}

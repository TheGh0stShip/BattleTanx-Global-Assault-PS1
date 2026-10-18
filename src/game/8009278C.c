extern int func_80097518(void *, int);

typedef struct {
    int pad0[2];
    int width;
    int height;
    int depth;
} Hdr8009278C;

typedef struct {
    unsigned char ready;
    volatile unsigned char b1;
} S8009278C;
extern S8009278C D_800EEF0C;
extern char D_800EEF44[];

int func_8009278C(Hdr8009278C *h, int fixed) {
    int w = 16;
    int size;

    if (fixed == 0) {
        w = h->width;
    }
    size = w * h->height * h->depth;
    return (size + 3) & ~3;
}

void func_800927C8(void) {
    D_800EEF0C.ready = 1;
    D_800EEF0C.b1 = 1;
}

void func_800927E4(unsigned char kind) {
    int ok = 1;

    if (kind == 1) {
        ok = func_80097518(D_800EEF44, 8) == 0;
    }
    if (ok) {
        D_800EEF0C.ready = 1;
    }
}

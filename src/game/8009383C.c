extern int func_800982B0(char *, unsigned int *, int *);
extern int func_80093960(unsigned int, int, int, int, int);

typedef struct {
    unsigned char b0;
    unsigned char stereo;
    volatile unsigned char busy;
    char pad3[25];
    int block;
} S8009383C;
extern S8009383C D_800EEFAC;

int func_8009383C(char *name, unsigned int start, unsigned int end, int extra, int a4, int a5) {
    unsigned int pos;
    int size;
    int offset;
    int len;
    int r = 0;

    if (func_800982B0(name, &pos, &size) != 0) {
        len = size;
        offset = r;
        if (start != 0) {
            offset = start * 3;
            offset = (unsigned int)offset / 40;
            offset &= -D_800EEFAC.block;
            if (D_800EEFAC.stereo == 0) {
                offset <<= 1;
            }
            offset <<= 11;
        }
        if (end != 0) {
            len = end * 3;
            len = (unsigned int)len / 40;
            len &= -D_800EEFAC.block;
            if (D_800EEFAC.stereo == 0) {
                len <<= 1;
            }
            len += extra;
            len <<= 11;
        }
        D_800EEFAC.busy = 1;
        r = func_80093960(pos + offset, len - offset, extra, a4, a5);
    }
    return r;
}

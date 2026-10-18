typedef struct {
    unsigned char b0;
    volatile unsigned char stereo;
    char pad2[26];
    int size;
    int mode;
} S80093590;
extern S80093590 D_800EEFAC;

void func_80093590(unsigned int mode) {
    switch (mode) {
    case 0:
        D_800EEFAC.size = 4;
        D_800EEFAC.mode = mode;
        D_800EEFAC.stereo = 1;
        break;
    case 1:
        D_800EEFAC.size = 8;
        D_800EEFAC.mode = mode;
        D_800EEFAC.stereo = 1;
        break;
    case 2:
        D_800EEFAC.size = 8;
        D_800EEFAC.mode = mode;
        D_800EEFAC.stereo = 1;
        break;
    case 3:
        D_800EEFAC.size = 16;
        D_800EEFAC.mode = mode;
        D_800EEFAC.stereo = 1;
        break;
    case 4:
        D_800EEFAC.size = 8;
        D_800EEFAC.mode = mode;
        D_800EEFAC.stereo = 0;
        break;
    case 5:
        D_800EEFAC.size = 16;
        D_800EEFAC.mode = mode;
        D_800EEFAC.stereo = 0;
        break;
    case 6:
        D_800EEFAC.size = 16;
        D_800EEFAC.mode = mode;
        D_800EEFAC.stereo = 0;
        break;
    case 7:
        D_800EEFAC.size = 32;
        D_800EEFAC.mode = mode;
        D_800EEFAC.stereo = 0;
        break;
    }
}

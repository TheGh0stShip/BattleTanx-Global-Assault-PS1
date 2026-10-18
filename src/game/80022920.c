extern int D_800A6074;
extern unsigned char D_800D302C;

int func_80022920(void) {
    if (D_800A6074 != 1) {
        return 4096;
    }
    switch (D_800D302C) {
    case 0:
    case 1:
        return 4096;
    case 2:
        return 4505;
    case 3:
        return 4915;
    case 4:
        return 5324;
    case 5:
        return 5734;
    }
    return 6144;
}

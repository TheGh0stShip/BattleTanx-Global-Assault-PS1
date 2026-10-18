typedef struct Sound {
    short x;
    short y;
    short z;
    unsigned short code;
} Sound;

extern int D_800C60D0;
extern unsigned short D_800ABA5C;
extern int D_800A6070;
extern unsigned short D_800ABA68[];
extern Sound D_800E4BFC[];
extern unsigned short func_8006186C(unsigned short);

void func_80061CC0(short x, short y, short z, unsigned short slot, unsigned short flags) {
    unsigned short kind;
    unsigned short high;
    unsigned short code;

    kind = flags & 0x7FFF;
    high = flags & 0x8000;
    if (D_800C60D0 == 5 && D_800ABA5C < 42) {
        if ((unsigned short)(flags - 28) >= 2) {
            if (D_800A6070 == 1 && D_800ABA68[0] == 0 && D_800ABA68[1] == 0 && kind == 0) {
                return;
            }
        } else {
            kind = 2;
            high = 1;
        }
        D_800E4BFC[D_800ABA5C].x = x >> 2;
        D_800E4BFC[D_800ABA5C].y = y >> 2;
        D_800E4BFC[D_800ABA5C].z = z;
        switch (flags) {
        case 28:
            code = 1;
            break;
        case 29:
            code = 5;
            break;
        default:
            code = func_8006186C(slot);
            break;
        }
        if (kind == 1) {
            code |= 0x8000;
        } else if (kind == 2) {
            code |= 0x4000;
        }
        if (high) {
            code |= 0x100;
        }
        D_800E4BFC[D_800ABA5C].code = code;
        if (D_800ABA5C < 42) {
            D_800ABA5C++;
        }
    }
}

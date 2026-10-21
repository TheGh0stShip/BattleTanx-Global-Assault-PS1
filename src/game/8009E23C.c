typedef struct { unsigned char b[240]; } PadSlot;
extern PadSlot D_800EF2D8[2];
extern PadSlot D_800EF4B8[2][4];

int func_8009E23C(PadSlot *p)
{
    int tap;
    int i;

    for (i = 0; i < 2; i++) {
        if (p == &D_800EF2D8[i]) {
            return (i + 1) << 4;
        }
        for (tap = 0; tap < 4; tap++) {
            if (p == &D_800EF4B8[i][tap]) {
                return ((i + 1) << 4) | (tap + 1);
            }
        }
    }
    return 255;
}

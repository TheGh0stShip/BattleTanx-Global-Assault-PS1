extern unsigned char D_800EF2D8[];
extern int D_800B8CC0;

unsigned char *func_8009E2B8(int port)
{
    unsigned char *p = D_800EF2D8;

    if (port & 0xF0) {
        p += 0xF0;
    }
    if (D_800B8CC0 != 0) {
        if ((p[0xE8] == 8 && (port & 0xF) == 0) || (port & 3) != 0) {
            p = *(unsigned char **)(p + 0xC) + (port & 3) * 0xF0;
        }
    }
    return p;
}

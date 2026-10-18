extern unsigned char D_800B7BFC[];

void func_8009B918(unsigned short *out)
{
    unsigned char *src;
    unsigned char *dst;
    int dist;
    int n;
    unsigned char b;
    int i;

    dist = 0;
    src = D_800B7BFC;
    dst = (unsigned char *)out;
    do {
        b = *src++;
        n = b;
        if (b < 0xF0) {
            if (dist != 0) {
                for (; n >= 0; n--) {
                    *dst = dst[-dist];
                    dst++;
                }
            } else {
                for (; n >= 0; n--) {
                    *dst++ = *src++;
                }
            }
        } else {
            dist = 0;
            if (n != 0xF0) {
                dist = ((n << 8) | *src++) - 0xF0FF;
            }
        }
    } while (dist != 0xF00);
    for (i = 4; i < 0x8800; i++) {
        out[i] ^= out[i - 4];
    }
}

typedef struct {
    unsigned char pad0[0xEC];
    char magic[2];
    unsigned char type;
    unsigned char blocks;
    unsigned char title[64];
    unsigned char pad130[0x1C];
    unsigned char clut[32];
    unsigned char icon[3][128];
    int size;
} CardHeader;

extern CardHeader D_800EE588;
extern unsigned short D_800B0E40[];
extern unsigned short D_800B0E64[];
extern unsigned short D_800B0E74[];
extern unsigned short D_800B0E84[];

extern void func_8008A7BC(void *, void *, int);
extern void func_8008AA48(void *, int, int);
extern int func_80086E38(int);
extern int func_80090184(char *);

void func_80088644(void *clut, void *icon1, void *icon2, void *icon3, unsigned char *title, int size)
{
    int i;
    int n;
    int total;
    unsigned char *p;

    D_800EE588.magic[0] = 'S';
    D_800EE588.magic[1] = 'C';
    func_8008A7BC(D_800EE588.clut, clut, 32);
    D_800EE588.type = 0x11;
    func_8008A7BC(D_800EE588.icon[0], icon1, 128);
    if (icon2 != 0) {
        D_800EE588.type = 0x12;
        func_8008A7BC(D_800EE588.icon[1], icon2, 128);
        if (icon3 != 0) {
            D_800EE588.type = 0x13;
            func_8008A7BC(D_800EE588.icon[2], icon3, 128);
        }
    }
    total = (size + func_80086E38(D_800EE588.type) + 0x1FFF) & ~0x1FFF;
    D_800EE588.size = total;
    D_800EE588.blocks = (unsigned int)total >> 13;
    func_8008AA48(D_800EE588.title, 0, 64);
    n = func_80090184(title);
    if (n >= 32) {
        n = 31;
    }
    p = D_800EE588.title;
    for (i = 0; i < n; i++) {
        unsigned char c = title[i];
        unsigned int code = 0;

        if (c >= 0x20 && c < 0x30) {
            code = D_800B0E40[c - 0x20];
        } else if (c >= 0x30 && c < 0x3A) {
            code = c + 0x821F;
        } else if (c >= 0x3A && c < 0x41) {
            code = D_800B0E64[c - 0x3A];
        } else if (c >= 0x41 && c < 0x5B) {
            code = c + 0x821F;
        } else if (c >= 0x5B && c < 0x61) {
            code = D_800B0E74[c - 0x5B];
        } else if (c >= 0x61 && c < 0x7B) {
            code = c - 0x7DE0;
        } else if (c >= 0x7B && c < 0x7F) {
            code = D_800B0E84[c - 0x7B];
        }
        *p++ = code >> 8;
        *p++ = code;
    }
}

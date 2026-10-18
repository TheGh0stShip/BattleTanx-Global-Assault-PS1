typedef struct Font {
    char data[0x4008];
} Font;

extern short D_800DDC58;
extern unsigned char D_800AEA43;
extern int D_800A48B4;
extern Font D_800D5B8C[];
extern char D_800BFCD8[];
extern void func_8008AA48(void *, int, int);
extern void func_80091D4C(Font *, int, int, int, int, char *);
extern void func_80054F8C(int, int, int, int, unsigned char *);

void func_8005F10C(void) {
    unsigned char color[4];

    func_8008AA48(color, 0, 4);
    color[3] = 255;
    if (D_800DDC58 != 512) {
        if (D_800AEA43 >= 31) {
            D_800AEA43 = 0;
        } else if (D_800AEA43 < 20) {
            func_80091D4C(&D_800D5B8C[D_800A48B4], 130, 100, 0xC8C8C8, 0, D_800BFCD8);
        }
        D_800AEA43++;
    }
    func_80054F8C(0, 0, 512, 256, color);
}

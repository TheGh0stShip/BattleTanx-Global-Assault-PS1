typedef struct { char data[0x5C]; } DrawEnv;
typedef struct { char data[0x14]; } DispEnv;
typedef struct { DrawEnv draw[2]; DispEnv disp; int ot; char pad[0x128 - 0xD0]; } Screen;
extern Screen D_800DDB9C[];
extern int D_800A48A8;
extern int D_800A48AC;
extern int D_800A48B0;
extern unsigned char D_800C60EC;
extern void func_8008BA04(void);
extern void func_80088870(int);
extern void func_80083B2C(int);
extern void func_8007FFD8(DispEnv *);
extern void func_8007FF18(DrawEnv *);

static inline Screen *current_screen(void)
{
    return &D_800DDB9C[D_800A48B0];
}

void func_8003A744(void)
{
    func_8008BA04();
    if (D_800C60EC != 0) {
        func_80088870(2);
    }
    if (D_800A48AC == 0) {
        D_800A48B0 ^= 1;
        func_80083B2C(3);
        func_8007FFD8(&current_screen()->disp);
    }
    func_8007FF18(&current_screen()->draw[D_800A48AC]);
    if ((unsigned int)(D_800A48A8 - 2) < 3) {
        if (++D_800A48AC == 2) {
            D_800A48AC = 0;
        }
    }
}

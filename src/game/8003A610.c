typedef struct { short x; short y; short w; short h; char rest[0x5C - 8]; } DrawEnv;
typedef struct { char data[0x14]; } DispEnv;
typedef struct { DrawEnv draw[2]; DispEnv disp; int ot; char pad[0x128 - 0xD0]; } Screen;
extern Screen D_800DDB9C[];
extern int D_800A48A8;
extern int D_800A48AC;
extern int D_800A48B0;
extern int D_800A48B4;
extern int func_8003A9CC(void);
extern void func_8008B9E4(int, int);
extern void func_8007F78C(void);
extern void func_8008B91C(short, short);
static inline void set_center(int w, int h)
{
    func_8008B91C((short)w / 2, (short)h / 2);
}
extern void func_8003A91C(void);

static inline Screen *current_screen(void)
{
    return &D_800DDB9C[D_800A48B0];
}

void func_8003A610(void)
{
    DrawEnv *env;

    D_800A48B4 ^= 1;
    func_8008B9E4(func_8003A9CC(), 4098);
    func_8007F78C();
    if (D_800A48A8 == 2 || D_800A48A8 == 4) {
        if (D_800A48AC == 0 || (D_800A48A8 == 4 && D_800A48AC == 1)) {
            env = &current_screen()->draw[D_800A48AC];
        } else {
            env = &current_screen()->draw[D_800A48AC];
        }
        set_center(env->w, env->h);
    }
    if ((unsigned int)(D_800A48A8 - 2) < 3) {
        func_8003A91C();
    }
}

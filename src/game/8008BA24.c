typedef struct {
    short x;
    short y;
    short w;
    short h;
} RECT;
typedef struct {
    RECT clip;
    short ofs[2];
    RECT tw;
    unsigned short tpage;
    unsigned char dtd;
    unsigned char dfe;
    unsigned char isbg;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
} DRAWENV;
extern int func_80094A5C(void);

DRAWENV *func_8008BA24(DRAWENV *env, int x, int y, int w, int h) {
    int pal = func_80094A5C();

    env->clip.x = x;
    env->clip.y = y;
    env->clip.w = w;
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    env->dtd = 1;
    env->clip.h = h;
    if (pal) {
        env->dfe = h < 289;
    } else {
        env->dfe = h < 257;
    }
    env->ofs[0] = x;
    env->ofs[1] = y;
    env->tpage = 10;
    env->isbg = 0;
    return env;
}

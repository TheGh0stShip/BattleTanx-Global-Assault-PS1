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
    unsigned char r0, g0, b0;
} DRAWENV;

typedef struct {
    unsigned long tag;
    unsigned long code[15];
} DR_ENV;

extern short D_800B0C64;
extern short D_800B0C66;

extern unsigned long func_800808C8(int, int);
extern unsigned long func_80080960(int, int);
extern unsigned long func_800809F8(int, int);
extern unsigned long func_800808A8(int, int, int);
extern unsigned long func_80080A14(RECT *);

void func_80080638(DR_ENV *dr_in, DRAWENV *env)
{
    DR_ENV *dr = dr_in;
    RECT rect;
    int len;

    dr->code[0] = func_800808C8(env->clip.x, env->clip.y);
    dr->code[1] = func_80080960((short)(env->clip.w + env->clip.x - 1), (short)(env->clip.y + env->clip.h - 1));
    dr->code[2] = func_800809F8(env->ofs[0], env->ofs[1]);
    dr->code[3] = func_800808A8(env->dfe, env->dtd, env->tpage);
    dr->code[4] = func_80080A14(&env->tw);
    dr->code[5] = 0xE6000000;
    len = 7;
    if (env->isbg) {
        rect.x = env->clip.x;
        rect.y = env->clip.y;
        rect.w = env->clip.w;
        rect.h = env->clip.h;
        rect.w = (rect.w < 0) ? 0 : (rect.w > D_800B0C64 - 1) ? D_800B0C64 - 1 : rect.w;
        rect.h = (rect.h < 0) ? 0 : (rect.h > D_800B0C66 - 1) ? D_800B0C66 - 1 : rect.h;
        if ((rect.x & 0x3F) || (rect.w & 0x3F)) {
            rect.x -= env->ofs[0];
            rect.y -= env->ofs[1];
            ((unsigned long *)dr)[len++] = 0x60000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            ((unsigned long *)dr)[len++] = *(unsigned long *)&rect.x;
            ((unsigned long *)dr)[len++] = *(unsigned long *)&rect.w;
        } else {
            ((unsigned long *)dr)[len++] = 0x02000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            ((unsigned long *)dr)[len++] = *(unsigned long *)&rect.x;
            ((unsigned long *)dr)[len++] = *(unsigned long *)&rect.w;
        }
    }
    ((unsigned char *)dr)[3] = len - 1;
}

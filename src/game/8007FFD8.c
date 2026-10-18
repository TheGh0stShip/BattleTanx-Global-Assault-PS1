typedef struct {
    short x;
    short y;
    short w;
    short h;
} RECT;

typedef struct {
    RECT disp;
    RECT screen;
    unsigned char isinter;
    unsigned char isrgb24;
    unsigned char pad0;
    unsigned char pad1;
} DISPENV;

typedef struct {
    volatile unsigned char level;
    unsigned char reverse;
    char pad02[12];
    unsigned char draw[92];
    volatile DISPENV disp;
} GpuState;

typedef struct {
    char pad[16];
    int (*ctl)(unsigned long cmd);
} GpuDriver;

extern GpuState D_800B0C62;
extern GpuDriver *D_800B0C58;
extern int (*D_800B0C5C)(char *fmt, ...);
extern char D_800C4CB4[];
extern int func_80094A5C(void);
extern void func_8008A7BC(void *dst, void *src, int len);

DISPENV *func_8007FFD8(DISPENV *env_in) {
    DISPENV *env = env_in;
    long h_start;
    long h_end;
    long v_start;
    long v_end;
    long mode;
    long fits;
    volatile RECT *rect;

    mode = 0x08000000;
    if (D_800B0C62.level >= 2) {
        D_800B0C5C(D_800C4CB4, env);
    }
    D_800B0C58->ctl(0x05000000 | ((env->disp.y & 0x3FF) << 10) | (env->disp.x & 0x3FF));
    rect = &D_800B0C62.disp.screen;
    if (rect->x != env->screen.x || rect->y != env->screen.y || rect->w != env->screen.w || rect->h != env->screen.h) {
        env->pad0 = func_80094A5C();
        h_start = env->screen.x * 10 + 608;
        v_start = env->screen.y + (env->pad0 ? 19 : 16);
        h_end = env->screen.w ? h_start + env->screen.w * 10 : h_start + 2560;
        v_end = env->screen.h ? v_start + env->screen.h : v_start + 240;
        h_start = h_start < 500 ? 500 : (h_start > 3290 ? 3290 : h_start);
        h_end = h_end < h_start + 80 ? h_start + 80 : (h_end > 3290 ? 3290 : h_end);
        v_start = v_start < 16 ? 16 : (v_start > (env->pad0 ? 310 : 256) ? (env->pad0 ? 310 : 256) : v_start);
        v_end = v_end < v_start + 2 ? v_start + 2
                                    : (v_end > (env->pad0 ? 312 : 258) ? (env->pad0 ? 312 : 258) : v_end);
        D_800B0C58->ctl(0x06000000 | ((h_end & 0xFFF) << 12) | (h_start & 0xFFF));
        D_800B0C58->ctl(0x07000000 | ((v_end & 0x3FF) << 10) | (v_start & 0x3FF));
    }
    if (*(long *)&D_800B0C62.disp.isinter != *(long *)&env->isinter ||
        (rect = &D_800B0C62.disp.disp, rect->x) != env->disp.x || rect->y != env->disp.y || rect->w != env->disp.w || rect->h != env->disp.h) {
        env->pad0 = func_80094A5C();
        if (env->pad0 == 1) {
            mode |= 0x08;
        }
        if (env->isrgb24) {
            mode |= 0x10;
        }
        if (env->isinter) {
            mode |= 0x20;
        }
        if (D_800B0C62.reverse) {
            mode |= 0x80;
        }
        if (env->disp.w > 280) {
            if (env->disp.w <= 352) {
                mode |= 0x01;
            } else if (env->disp.w <= 400) {
                mode |= 0x40;
            } else if (env->disp.w <= 560) {
                mode |= 0x02;
            } else {
                mode |= 0x03;
            }
        }
        fits = env->disp.h <= (env->pad0 ? 288 : 256);
        if (!fits) {
            mode |= 0x24;
        }
        D_800B0C58->ctl(mode);
    }
    func_8008A7BC((void *)&D_800B0C62.disp, env, sizeof(DISPENV));
    return env;
}

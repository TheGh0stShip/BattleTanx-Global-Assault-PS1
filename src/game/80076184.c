typedef struct DrawEnv {
    short x;
    short y;
    char pad[88];
} DrawEnv;

typedef struct DispEnv {
    char data[20];
} DispEnv;

typedef struct FrameBuffer {
    DrawEnv draw[2];
    DispEnv disp;
    char pad[92];
} FrameBuffer;

extern int D_800A48B0;
extern int D_800A48AC;
extern unsigned char D_800AEA43;
extern FrameBuffer D_800DDB9C[];
extern char D_800AE9E0[];
extern void func_8003A610(void);
extern void func_8007FA74(int);
extern void func_80088870(int);
extern void func_8007FFD8(DispEnv *);
extern void func_8007FF18(DrawEnv *);
extern void func_8007FCE8(void *, int, int);
extern void func_8003A8F4(void);

static inline DispEnv *current_disp(void) {
    FrameBuffer *fb = &D_800DDB9C[D_800A48B0];
    return &fb->disp;
}

static inline DrawEnv *current_draw(void) {
    FrameBuffer *fb = &D_800DDB9C[D_800A48B0];
    return &fb->draw[D_800A48AC];
}

void func_80076184(void) {
    DrawEnv *draw;

    do {
        D_800AEA43++;
        func_8003A610();
        func_8007FA74(0);
        func_80088870(2);
        D_800A48B0 ^= 1;
        func_8007FFD8(current_disp());
        func_8007FF18(current_draw());
        draw = current_draw();
        func_8007FCE8(D_800AE9E0, draw->x, draw->y);
        func_8003A8F4();
    } while (D_800AEA43 < 150);
    D_800AEA43 = 0;
}

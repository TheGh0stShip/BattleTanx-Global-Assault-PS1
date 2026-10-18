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

typedef struct Scene {
    int pad0;
    void *data;
} Scene;

extern int D_800A48B0;
extern int D_800A48AC;
extern unsigned char D_800AEA41;
extern unsigned char D_800AEA44;
extern unsigned char D_800AEA45;
extern unsigned char D_800AAD00;
extern unsigned char D_800AACE1;
extern FrameBuffer D_800DDB9C[];
extern char D_800AE9E0[];
extern int func_8007FA74(int);
extern void func_8003A610(void);
extern void func_8007FFD8(DispEnv *);
extern void func_8007FF18(DrawEnv *);
extern void func_8007FCE8(void *, int, int);
extern void func_8003A8F4(void);
extern void func_80084898(int);
extern void func_80075CB0(void);
extern Scene *func_8006A7FC(void);
extern void func_8005EB6C(void *);
extern void func_8005EFE8(void);
extern void func_8005F10C(void);

static inline DispEnv *current_disp(void) {
    FrameBuffer *fb = &D_800DDB9C[D_800A48B0];
    return &fb->disp;
}

static inline DrawEnv *current_draw(void) {
    FrameBuffer *fb = &D_800DDB9C[D_800A48B0];
    return &fb->draw[D_800A48AC];
}

void func_80075E60(void) {
    DrawEnv *draw;

    if (D_800AEA44 != 0 && func_8007FA74(1) == 0) {
        func_8003A610();
        D_800A48B0 ^= 1;
        func_8007FFD8(current_disp());
        func_8007FF18(current_draw());
        if (D_800AAD00 == 0) {
            draw = current_draw();
            func_8007FCE8(D_800AE9E0, draw->x, draw->y);
        }
        D_800AEA44 ^= 1;
    } else if (D_800AEA44 == 0 && func_8007FA74(1) == 0) {
        func_80084898(10);
        if (D_800AEA41 != 0) {
            func_80075CB0();
        } else if (D_800AEA45 != 0) {
            func_8005EB6C(func_8006A7FC()->data);
        } else if (D_800AACE1 != 0) {
            func_8005EFE8();
        } else {
            func_8005F10C();
        }
        func_8003A8F4();
        D_800AEA44 ^= 1;
    }
}

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct Mat {
    int m[8];
} Mat;

typedef struct Camera {
    int pad0[2];
    Vec pos;
    int pad14[15];
    Mat view;
    int pad70[11];
} Camera;

typedef struct View {
    unsigned char pad0;
    unsigned char current;
    short pad2;
    Camera cameras[1];
} View;

typedef struct ModelData {
    int pad0[2];
    int count;
    int pad0C[3];
    int verts;
} ModelData;

typedef struct Model {
    ModelData *data;
    char *prims;
} Model;

typedef struct LightDef {
    int life;
    short radius;
    unsigned short intensity;
    short grow;
    unsigned char color_min[3];
    unsigned char color_max[3];
    short shrink;
    short lerp_color;
    short fixed_scale;
    short pad16;
    short model;
    short pad1A;
} LightDef;

typedef struct SVec {
    short x;
    short y;
    short z;
    short pad;
} SVec;

typedef struct Light {
    int pad0;
    short pad4;
    short radius;
    int type;
    int life;
    int timer;
    Vec pos;
    SVec dir;
    SVec axis;
    short intensity;
    short grow;
    unsigned char color[3];
    unsigned char color_start[3];
    unsigned char attached;
} Light;

typedef struct Work {
    char data[16392];
} Work;

extern LightDef D_800AE184[];
extern Model *D_800D2E14[];
extern View D_800D3034;
extern Work D_800D5B94[];
extern int D_800A48B4;
extern int D_800A4CC0;
extern int D_800A4CC4;
extern int D_800A4CC8;
extern int D_800A4CCC;
extern int func_8008AE30(int, int);
extern unsigned int func_80086C84(void);
extern void func_8008A4B8(Mat *, int);
extern void func_8008A62C(Mat *, int, int, int);
extern void func_8003E0E4(Mat *, Mat *, Mat *);
extern void *func_8006A26C(int);
extern void func_8007E570(Mat *, int *, void *, int);
extern void func_8003BC68(int);
extern void func_8008BC28(int);
extern void func_8007D580(ModelData *, void *, Work *, char *, int, int, int, int *, int, int, int, int, int, int, int);

static inline int shr12(int v) {
    return v < 0 ? -(-v >> 12) : v >> 12;
}

static inline int round12(int v) {
    return v >= 0 ? shr12(v + 2048) : shr12(v - 2048);
}

static inline void set_scale(Mat *m, int sx, int sy) {
    m->m[0] = sx;
    m->m[1] = 0;
    m->m[2] = sy;
    m->m[3] = 0;
    m->m[4] = sx;
    m->m[5] = 0;
    m->m[6] = 0;
    m->m[7] = 0;
}

void func_80071ECC(Light *light) {
    Mat local;
    Mat world;
    Vec d;
    int tmp[2];
    Camera *cam;
    Vec *pos;
    int count;
    int angle;
    int jitter;
    unsigned int rnd;
    Work *work;
    Model *model;
    void *buf;

    count = D_800D2E14[D_800AE184[light->type].model]->data->count;
    cam = &D_800D3034.cameras[D_800D3034.current];
    pos = &light->pos;
    d.x = ((pos->x - cam->pos.x) >= 0 ? (((pos->x - cam->pos.x) + 2048) >= 0 ? (((pos->x - cam->pos.x) + 2048)) >> 12 : -(-(((pos->x - cam->pos.x) + 2048)) >> 12)) : (((pos->x - cam->pos.x) - 2048) >= 0 ? (((pos->x - cam->pos.x) - 2048)) >> 12 : -(-(((pos->x - cam->pos.x) - 2048)) >> 12)));
    d.y = ((pos->y - cam->pos.y) >= 0 ? (((pos->y - cam->pos.y) + 2048) >= 0 ? (((pos->y - cam->pos.y) + 2048)) >> 12 : -(-(((pos->y - cam->pos.y) + 2048)) >> 12)) : (((pos->y - cam->pos.y) - 2048) >= 0 ? (((pos->y - cam->pos.y) - 2048)) >> 12 : -(-(((pos->y - cam->pos.y) - 2048)) >> 12)));
    do {
        d.z = ((pos->z - cam->pos.z) >= 0 ? (((pos->z - cam->pos.z) + 2048) >= 0 ? (((pos->z - cam->pos.z) + 2048)) >> 12 : -(-(((pos->z - cam->pos.z) + 2048)) >> 12)) : (((pos->z - cam->pos.z) - 2048) >= 0 ? (((pos->z - cam->pos.z) - 2048)) >> 12 : -(-(((pos->z - cam->pos.z) - 2048)) >> 12)));
        __asm__("" : : "r"(&local));
        set_scale(&local, light->radius, light->intensity);
        angle = func_8008AE30(-d.x, -d.z);
        rnd = func_80086C84();
        angle *= 16;
        jitter = ((int)((rnd >> 16) * 8193) >> 16) + 0xF000;
        func_8008A4B8(&local, (angle + jitter) & 0xFFFF);
        func_8008A62C(&local, d.x, d.y, d.z);
        func_8003E0E4(&D_800D3034.cameras[D_800D3034.current].view, &local, &world);
        buf = func_8006A26C(count << 3);
        func_8007E570(&world, &D_800D2E14[D_800AE184[light->type].model]->data->verts, buf, count);
        func_8003BC68((light->color_start[2] << 16) + (light->color_start[1] << 8) | light->color_start[0]);
        func_8008BC28(1);
        work = &D_800D5B94[D_800A48B4];
        func_8007D580(D_800D2E14[D_800AE184[light->type].model]->data, buf, work,
                      D_800D2E14[D_800AE184[light->type].model]->prims + 8, 0, 0, 0, tmp, 0, 0, 2304,
                      D_800A4CC0, D_800A4CC4, D_800A4CC8, D_800A4CCC);
    } while (0);
}

typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;

typedef struct Matrix {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct Camera {
    int pad[2];
    Vector pos;
    char pad2[0x50 - 0x14];
    Matrix rot;
} Camera;

typedef struct Object {
    char pad[0x5C];
    Camera *camera;
    char pad2[0x114 - 0x60];
} Object;

typedef struct SVector {
    short x;
    short y;
    short z;
    short pad;
} SVector;

typedef struct ScreenXY {
    short x;
    short y;
} ScreenXY;

extern Object D_800E3E68[];

static inline void gte_SetRotMatrix(Matrix *r) {
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     :
                     : "r"(r)
                     : "$12", "$13", "$14");
}

static inline void gte_ldv0(SVector *v) {
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)" : : "r"(v));
}

static inline void gte_rtps(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x0180001");
}

static inline void gte_stsxy(ScreenXY *v) {
    __asm__ volatile("swc2 $14, 0(%0)" : : "r"(v) : "memory");
}

static inline int round_fixed(int x) {
    return x >= 0 ? (x + 2048 >= 0 ? (x + 2048) >> 12 : -(-(x + 2048) >> 12))
                  : (x - 2048 >= 0 ? (x - 2048) >> 12 : -(-(x - 2048) >> 12));
}

int func_8006218C(Vector *pos, int *out, int index) {
    Object *object;
    Camera *camera;
    int unused[2];
    int delta[3];
    int diff;
    SVector local;
    ScreenXY screen;

    if (index == 127) {
        object = 0;
    } else {
        object = &D_800E3E68[index];
    }
    camera = object->camera;
    diff = pos->x - camera->pos.x;
    delta[0] = round_fixed(diff);
    diff = pos->y - camera->pos.y;
    delta[1] = round_fixed(diff);
    diff = pos->z - camera->pos.z;
    delta[2] = round_fixed(diff);
    local.x = delta[0];
    local.y = delta[1];
    local.z = delta[2];
    gte_SetRotMatrix(&object->camera->rot);
    gte_ldv0(&local);
    gte_rtps();
    gte_stsxy(&screen);
    if ((unsigned short)(screen.x + 9) < 531 && screen.y >= -9) {
        if (screen.y < 250) {
            out[0] = screen.x;
            out[1] = screen.y;
            goto ok;
        }
        return 0;
    }
    return 0;
ok:
    return 1;
}

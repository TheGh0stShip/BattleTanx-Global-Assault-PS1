typedef struct SVec3 {
    short x;
    short y;
    short z;
} SVec3;
typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct View {
    short fov;
    short unk02;
    short unk04;
    char pad06[2];
    Vector pos;
    SVec3 rot;
    char pad1A[2];
    SVec3 color;
    char pad22[2];
    short scale_x;
    short scale_y;
} View;
extern SVec3 D_800BD4D0;
extern SVec3 D_800BD4D8;

static inline void zero_vec(Vector *v) {
    v->x = 0;
    v->y = 0;
    v->z = 0;
}

static inline void copy_svec(SVec3 *dst, SVec3 *src) {
    short x = src->x;
    short y = src->y;
    short z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

void func_80014DB4(View *view) {
    view->fov = 1092;
    view->unk02 = 0;
    view->unk04 = 0;
    zero_vec(&view->pos);
    copy_svec(&view->rot, &D_800BD4D0);
    copy_svec(&view->color, &D_800BD4D8);
    view->scale_x = 4096;
    view->scale_y = 4096;
}

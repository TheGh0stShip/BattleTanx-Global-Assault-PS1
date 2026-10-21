typedef struct SVec {
    short x;
    short y;
    short z;
    short pad;
} SVec;

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct Vec4 {
    int x;
    int y;
    int z;
    int pad;
} Vec4;

typedef struct Mat {
    int w[5];
    int t[3];
} Mat;

typedef struct Part {
    int pad0[2];
    struct Part *next;
    SVec offset;
    Vec pos;
    int pad20[3];
    unsigned short rx;
    unsigned short ry;
    unsigned short rz;
} Part;

typedef struct Model {
    int pad0[2];
    int id;
    int pad0C;
    char info[12];
    Part *parts;
} Model;

typedef struct Camera {
    int pad0[2];
    Vec pos;
    char pad14[60];
    char view[76];
} Camera;

typedef struct CameraSet {
    unsigned char pad0;
    unsigned char current;
    char pad2[2];
    Camera cams[1];
} CameraSet;

extern CameraSet D_800D3034;
extern char *func_80069C2C(int, void *);
extern void func_8008A48C(Mat *, int);
extern void func_8008A4B8(Mat *, int);
extern void func_8008A4E4(Mat *, int);
extern void func_8008A63C(Mat *, SVec *, SVec *);
extern void func_8003E0E4(void *, Mat *, char *);

static inline void set_identity(Mat *m) {
    __asm__ volatile("li $8, 4096\n\tsw $8, 0(%0)\n\tsw $0, 4(%0)\n\tsw $8, 8(%0)\n\tsw $0, 12(%0)\n\tsw $8, 16(%0)\n\tsw $0, 20(%0)\n\tsw $0, 24(%0)\n\tsw $0, 28(%0)"
                     :
                     : "r"(m)
                     : "$8", "memory");
}

static inline int div_fixed(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline int round_fixed(int v) {
    if (v >= 0) {
        return div_fixed(v + 2048);
    }
    return div_fixed(v - 2048);
}

static inline void set_translation(Mat *m, Vec4 *d) {
    Camera *cam = &D_800D3034.cams[D_800D3034.current];

    m->t[0] = ((d->x - cam->pos.x) >= 0 ? (((d->x - cam->pos.x) + 2048) >= 0 ? (((d->x - cam->pos.x) + 2048)) >> 12 : -(-(((d->x - cam->pos.x) + 2048)) >> 12)) : (((d->x - cam->pos.x) - 2048) >= 0 ? (((d->x - cam->pos.x) - 2048)) >> 12 : -(-(((d->x - cam->pos.x) - 2048)) >> 12)));
    m->t[1] = ((d->y - cam->pos.y) >= 0 ? (((d->y - cam->pos.y) + 2048) >= 0 ? (((d->y - cam->pos.y) + 2048)) >> 12 : -(-(((d->y - cam->pos.y) + 2048)) >> 12)) : (((d->y - cam->pos.y) - 2048) >= 0 ? (((d->y - cam->pos.y) - 2048)) >> 12 : -(-(((d->y - cam->pos.y) - 2048)) >> 12)));
    m->t[2] = ((d->z - cam->pos.z) >= 0 ? (((d->z - cam->pos.z) + 2048) >= 0 ? (((d->z - cam->pos.z) + 2048)) >> 12 : -(-(((d->z - cam->pos.z) + 2048)) >> 12)) : (((d->z - cam->pos.z) - 2048) >= 0 ? (((d->z - cam->pos.z) - 2048)) >> 12 : -(-(((d->z - cam->pos.z) - 2048)) >> 12)));
}

void func_80073FF4(Model *model) {
    Part *part = model->parts;
    char *out;
    Vec4 d;
    SVec o;
    Mat m;

    if (part == 0) {
        return;
    }
    out = func_80069C2C(model->id, model->info);
    if (out == 0) {
        return;
    }
    do {
        set_identity(&m);
        func_8008A48C(&m, part->rx);
        func_8008A4B8(&m, part->ry);
        func_8008A4E4(&m, part->rz);
        func_8008A63C(&m, &part->offset, &o);
        d.x = part->pos.x - (o.x << 12);
        d.y = part->pos.y - (o.y << 12);
        d.z = part->pos.z - (o.z << 12);
        set_translation(&m, &d);
        func_8003E0E4(D_800D3034.cams[D_800D3034.current].view, &m, out);
        part = part->next;
        out += 32;
    } while (part != 0);
}

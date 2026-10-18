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
typedef struct Matrix {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;
typedef struct View {
    char pad00[0x90];
    SVec3 angle;
    SVec3 offset;
} View;
void func_800150A4(SVec3 *);
void func_80015090(Vector *);

static inline void gte_SetRotMatrix(Matrix *m) {
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     :
                     : "r"(m)
                     : "$12", "$13", "$14");
}

static inline void gte_rtv0(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x041E012");
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void add_vec(Vector *v, int *t) {
    v->x += t[0];
    v->y += t[1];
    v->z += t[2];
}

void func_80015318(View *view, short blend, Matrix *m, SVec3 *out, Vector *result) {
    out->x = 0;
    out->y = to_int(blend * (view->angle.y << 2) + (4096 - blend) * (view->offset.y << 2));
    out->z = to_int(blend * (view->angle.x << 2));
    gte_SetRotMatrix(m);
    func_800150A4(out);
    gte_rtv0();
    func_80015090(result);
    add_vec(result, m->t);
}

typedef struct Matrix {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;
typedef struct Vec4 {
    int vx;
    int vy;
    int vz;
    int pad;
} Vec4;
typedef struct Camera {
    char pad00[8];
    int x;
    int y;
    int z;
} Camera;
void func_80015808(Matrix *, Camera *);
void func_8008AA48(void *, int, int);
void func_8008A65C(Matrix *, Vec4 *, int *);

void func_80014864(Matrix *m, Camera *cam) {
    Vec4 tmp;
    Vec4 v;

    func_80015808(m, cam);
    func_8008AA48(&v, 0, sizeof(v));
    v.vx = (-cam->x) >= 0 ? ((-cam->x) + 2048 >= 0 ? ((-cam->x) + 2048) >> 12 : -(-((-cam->x) + 2048) >> 12))
                              : ((-cam->x) - 2048 >= 0 ? ((-cam->x) - 2048) >> 12 : -((2048 - (-cam->x)) >> 12));
    v.vy = (-cam->y) >= 0 ? ((-cam->y) + 2048 >= 0 ? ((-cam->y) + 2048) >> 12 : -(-((-cam->y) + 2048) >> 12))
                              : ((-cam->y) - 2048 >= 0 ? ((-cam->y) - 2048) >> 12 : -((2048 - (-cam->y)) >> 12));
    v.vz = (-cam->z) >= 0 ? ((-cam->z) + 2048 >= 0 ? ((-cam->z) + 2048) >> 12 : -(-((-cam->z) + 2048) >> 12))
                              : ((-cam->z) - 2048 >= 0 ? ((-cam->z) - 2048) >> 12 : -((2048 - (-cam->z)) >> 12));
    tmp = v;
    func_8008A65C(m, &tmp, m->t);
}

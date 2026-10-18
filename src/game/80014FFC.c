typedef struct SVector {
    short x;
    short y;
    short z;
    short pad;
} SVector;
typedef struct Matrix Matrix;
void func_8008AA48(void *, int, int);
void func_80015808(Matrix *, SVector *);

void func_80014FFC(Matrix *m, SVector *rot) {
    SVector tmp;
    SVector r;

    func_8008AA48(&r, 0, sizeof(r));
    r.x = -rot->x;
    r.y = -rot->y;
    r.z = (unsigned short)rot->z + 0x8000;
    tmp = r;
    func_80015808(m, &tmp);
}

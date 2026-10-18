typedef struct SVec3 {
    short x;
    short y;
    short z;
} SVec3;

void func_80015924(SVec3 *v) {
    v->x = (v->x * 6553) >> 12;
    v->y = (v->y * 6553) >> 12;
    v->z = (v->z * 6553) >> 12;
}

typedef struct { int x, y, z; } Vector;
typedef struct { int pad0[2]; int x; int z; unsigned short arg; short pad1; int pad2[6]; int target; } Emitter;
void func_8006A1BC(int, Vector *, int, int, int);

void func_80034DF4(Emitter *e) {
    Vector pos;
    Vector tmp;

    if (e->target != 0) {
        tmp.x = e->x;
        tmp.y = 0;
        tmp.z = e->z;
        pos = tmp;
        func_8006A1BC(e->target, &pos, 0, e->arg, 0);
    }
}

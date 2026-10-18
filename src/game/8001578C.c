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
    short ax;
    short ay;
    short az;
    short pad06;
    Vector pos;
    char pad14[0x50 - 0x14];
    Matrix world;
    Matrix inverse;
    char pad90[0xA0 - 0x90];
} View;
void func_80014FFC(Matrix *, View *);
void func_80014864(Matrix *, View *);

void func_8001578C(View *view) {
    View inv;

    func_80014FFC(&view->world, view);
    inv.ax = -view->ax;
    inv.ay = -view->ay;
    inv.az = view->az;
    {
        int x = view->pos.x;
        int y = view->pos.y;
        int z = view->pos.z;

        inv.pos.x = -x;
        inv.pos.y = -y;
        inv.pos.z = z;
    }
    func_80014864(&view->inverse, &inv);
}

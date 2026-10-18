typedef struct { int x, y, z; } Vector;
typedef struct { int pad[3]; Vector v; } Camera;
extern Vector *D_800A4B14;
extern Camera D_800DE194;

void func_8003DC44(int i, Vector *out) {
    if (D_800A4B14[i].x != 0) {
        *out = D_800A4B14[i];
        return;
    }
    *out = D_800DE194.v;
}

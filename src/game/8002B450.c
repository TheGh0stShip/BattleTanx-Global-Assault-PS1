typedef struct { int x, y, z; } Vector;
typedef struct { int pad[2]; Vector pos; int pad2[3]; int kind; int pad3; unsigned short angle; } Pickup;
extern int D_800A47AC[];
void func_80069D68(int, Vector *, int, int, int, int, int);

void func_8002B450(Pickup *p) {
    int color;

    color = 4505;
    if (p->kind != 1) {
        if (p->kind == 0) {
            color = 4505;
        } else if (p->kind == 3) {
            color = 20889;
        }
    } else {
        color = 8601;
    }
    func_80069D68(D_800A47AC[p->kind], &p->pos, 0, p->angle, 0, color, 0);
}

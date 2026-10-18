typedef struct { int x, y, z; } Vector;
typedef struct { int pad[2]; Vector pos; unsigned short angle; short pad2; short health; short max_health; int model_ok; int pad3; int model_damaged; } Prop;
void func_8006A1BC(int, Vector *, int, int, int);

void func_80032324(Prop *p) {
    Prop *q = p;

    if (p->max_health / 2 < p->health) {
        func_8006A1BC(p->model_ok, &p->pos, 0, p->angle, 0);
    } else {
        func_8006A1BC(q->model_damaged, &q->pos, 0, q->angle, 0);
    }
}

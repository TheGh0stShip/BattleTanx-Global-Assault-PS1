typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    int a;
    int b;
    Vector point;
    char pad14[20];
} Hit;
typedef struct {
    int kind;
    int time;
    short step;
    short pad0A;
    Vector mid;
    int dist;
    Vector goal;
    int goal_dist;
} Wander;
typedef struct {
    int id;
    char pad04[4];
    Vector position;
    char pad14[0x2C - 0x14];
    unsigned short heading;
    char pad2E[0x184 - 0x2E];
    Wander wander;
    char pad1B0[0x218 - 0x1B0];
    int status;
} Tank;
extern int D_800D2FE0;
extern short D_800C628C;
extern void func_80049680(Vector *, int, int);
extern void func_80049840(Vector *, Vector *);
extern unsigned short func_80019D80(Vector *, Vector *, int, int, int, Hit *);
extern int func_800495D8(Vector *, Vector *);
extern void func_8004E0BC(Tank *);
extern void func_8004D804(Tank *);

void func_8004EA1C(Tank *tank) {
    Hit hit;
    Vector dir;
    Vector end;
    Wander *w;
    Vector *point;

    tank->status |= 0x100;
    w = &tank->wander;
    w->kind = 2;
    w->step = 0;
    w->time = D_800D2FE0;
    func_80049680(&dir, 0x1F40000, tank->heading);
    end.x = tank->position.x;
    end.z = tank->position.z;
    func_80049840(&end, &dir);
    D_800C628C = 0;
    if (func_80019D80(&tank->position, &end, 0x2C7007, 300, tank->id, &hit) != 0) {
        point = &hit.point;
    } else {
        point = &end;
    }
    w->mid.x = (tank->position.x + point->x) >> 1;
    w->mid.z = (tank->position.z + point->z) >> 1;
    w->dist = func_800495D8(&w->mid, point);
    w->goal.x = w->mid.x;
    w->goal.z = w->mid.z;
    w->goal_dist = w->dist;
    func_8004E0BC(tank);
    func_8004D804(tank);
}

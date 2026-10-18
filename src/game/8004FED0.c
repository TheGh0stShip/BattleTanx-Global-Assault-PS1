typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    unsigned int kind;
    char pad4[0x1C - 4];
    Vector anchor;
    int radius;
} Move;
typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0x184 - 0x14];
    Move move;
} Tank;
typedef struct {
    int distance;
    int speed;
    unsigned short heading;
    char padA[0x10 - 0xA];
    int timer;
} Steer;
extern void func_8004960C(Vector *, Vector *, Vector *);
extern unsigned short func_80049740(Vector *);
extern void func_80049680(Vector *, int, int);
extern void func_80049840(Vector *, Vector *);
extern int func_800495D8(Vector *, Vector *);
extern void func_80048F2C(Tank *, Steer *);
extern void func_80048AFC(Tank *, Steer *);

void func_8004FED0(Tank *tank, Steer *steer) {
    Vector delta;
    Vector offset;
    Vector target;
    Vector to_target;
    unsigned short angle;
    Move *move = &tank->move;

    switch (move->kind) {
    case 0:
    case 1:
        break;
    case 2:
    case 3:
    case 4:
        func_8004960C(&delta, &tank->move.anchor, &tank->position);
        angle = func_80049740(&delta) + 0x1556;
        func_80049680(&offset, move->radius, angle);
        target.x = move->anchor.x;
        target.z = move->anchor.z;
        func_80049840(&target, &offset);
        func_8004960C(&to_target, &tank->position, &target);
        steer->distance = func_800495D8(&tank->position, &target);
        steer->heading = func_80049740(&to_target);
        steer->speed = 1228;
        steer->timer = 0;
        func_80048F2C(tank, steer);
        func_80048AFC(tank, steer);
        break;
    }
}

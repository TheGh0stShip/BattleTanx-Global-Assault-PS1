static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
            : "=&r"(low), "=&r"(high)
            : "r"(a), "r"(b));
    return low;
}

typedef struct Vector {
    int x;
    int y;
    int z;
    int pad;
} Vector;

typedef struct AiTankType {
    char pad00[0xA8];
    unsigned short reach;
    short ratio;
    char padAC[0xD0 - 0xAC];
} AiTankType;

typedef struct AiTank {
    int id;
    char pad04[0x8 - 0x4];
    Vector position;
    char pad18[0x2C - 0x18];
    unsigned short heading;
    char pad2E[0x9C - 0x2E];
    int type;
    char padA0[0x180 - 0xA0];
    int status;
    char pad184[0x1F8 - 0x184];
    int speed;
} AiTank;

typedef struct Move {
    int dist;
    int speed;
    unsigned short heading;
    char pad0A[0x10 - 0xA];
    int arrived;
} Move;

extern AiTankType D_800A4EF4[];
extern unsigned short D_800C628C;

void *func_8004CFB4(AiTank *);
int func_8004CFFC(AiTank *, void *);
void *func_8004DFEC(AiTank *);
int func_8004986C(Vector *, void *, int);
unsigned short func_80019D80(Vector *, Vector *, int, unsigned short, int, void *);
void func_8004960C(Vector *, Vector *, void *);
int func_800495D8(Vector *, void *);
unsigned short func_80049740(Vector *);

void func_80048900(AiTank *tank, Move *move) {
    register void *target = 0;
    void *goal;
    Vector delta;

    __asm__("" : "+r"(target));
    goal = func_8004CFB4(tank);
    if (func_8004CFFC(tank, goal)) {
        Vector probe;
        Vector *probe_ptr;
        char hit[40];
        unsigned short reach;

        move->dist = 0;
        move->heading = tank->heading;
        move->speed = 0;
        move->arrived = 1;
        if (tank->status & 0x82) {
            return;
        }
        target = func_8004DFEC(tank);
        if (target == 0) {
            return;
        }
        probe_ptr = &probe;
        __asm__("" : "+r"(probe_ptr));
        probe.x = tank->position.x;
        probe.z = tank->position.z;
        if (!func_8004986C(probe_ptr, target, 0xBB8000)) {
            return;
        }
        reach = D_800A4EF4[tank->type].reach;
        D_800C628C = 0;
        if (func_80019D80(&tank->position, probe_ptr, 0x80000, reach, tank->id, hit)) {
            return;
        }
        func_8004960C(&delta, &tank->position, target);
        move->dist = func_800495D8(&tank->position, target);
        move->heading = func_80049740(&delta);
        move->arrived = 0;
        if (!(tank->status & 0x200)) {
            tank->status |= 0x200;
        }
        move->speed = fixed_mul(4096, tank->speed);
    } else {
        func_8004960C(&delta, &tank->position, goal);
        move->dist = func_800495D8(&tank->position, goal);
        move->speed = fixed_mul(4096, tank->speed);
        move->heading = func_80049740(&delta);
        move->arrived = 0;
    }
}

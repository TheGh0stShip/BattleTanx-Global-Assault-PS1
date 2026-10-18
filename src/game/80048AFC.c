typedef struct Vector {
    int x;
    int y;
    int z;
    int pad;
} Vector;

typedef struct Move {
    int dist;
    int speed;
    unsigned short heading;
    char pad0A[0x10 - 0xA];
    int arrived;
} Move;

typedef struct AiTank {
    char pad000[0x2C];
    unsigned short heading;
    char pad02E[0x34 - 0x2E];
    int velocity_x;
    int velocity_z;
    char pad03C[0x4E - 0x3C];
    unsigned short course;
    char pad050[0x168 - 0x50];
    int stuck_until;
    int traction;
} AiTank;

extern int D_800DE30C;
extern int D_800D2FE0;

unsigned short func_80047AC8(unsigned short *heading, unsigned int target, unsigned int step);
short func_8001F294(int *velocity);
int func_80043F40(AiTank *, int power, unsigned int heading, unsigned int old_heading);
unsigned int func_80086C84(void);
unsigned short func_80049740(Vector *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline int fixed_to_int_result(int value) {
    int result;

    if (value >= 0) {
        result = value >> 12;
    } else {
        result = -(-value >> 12);
    }
    return result;
}

void func_80048AFC(AiTank *tank, Move *move) {
    unsigned short old_heading;
    int step;
    int push;
    int traction;
    int remaining;
    int clamped;
    Vector velocity;

    old_heading = tank->heading;
    if (D_800DE30C > 32767) {
        step = 5824;
    } else {
        step = fixed_to_int_result(fixed_mul(D_800DE30C, 0x2D8000));
    }
    step = func_80047AC8(&tank->heading, move->heading, (unsigned short)step);
    push = 0;
    if ((unsigned short)step < 183 || move->dist > 0x63FFF) {
        push = move->speed;
    }
    tank->heading += func_8001F294(&tank->velocity_x);
    remaining = tank->stuck_until - D_800D2FE0;
    traction = fixed_mul(4055, tank->traction);
    if (remaining > 0) {
        if (remaining >= 5) {
            func_80043F40(tank, -2048, old_heading, old_heading);
        } else if (func_80043F40(tank, 1228, tank->heading, old_heading) & 0x10) {
            traction += 1228;
        }
    } else if (func_80043F40(tank, push, tank->heading, old_heading) & 0x10) {
        push = fixed_mul(0x8000000, tank->traction);
        traction += 1228;
        tank->stuck_until = D_800D2FE0 + 14;
        if (!(func_80086C84() & 1)) {
            push = -push;
        }
        push = fixed_to_int(push);
        tank->heading += push;
    }
    clamped = traction;
    if (clamped > 4096) {
        clamped = 4096;
    }
    tank->traction = clamped;
    velocity.x = tank->velocity_x;
    velocity.z = tank->velocity_z;
    tank->course = func_80049740(&velocity);
}

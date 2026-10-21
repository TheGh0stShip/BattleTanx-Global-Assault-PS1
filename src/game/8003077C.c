typedef struct Segment {
    char pad0[0xC];
    struct Segment *next;
    char pad10[0x22 - 0x10];
    unsigned short type;
    char pad24[0x34 - 0x24];
    int timer;
} Segment;

typedef struct {
    int x;
    int z;
} Pos2;

typedef struct {
    char pad0[8];
    Pos2 pos;
    int length;
    char pad14[0x20 - 0x14];
    unsigned short angle;
    char pad22[0x24 - 0x22];
    int width;
    int offset;
    Segment *segments;
    short period;
    unsigned char sound;
    char pad33;
    int timer;
    unsigned char state;
    unsigned char phase;
    unsigned short delay;
} Bridge;

extern int D_800D2FE0;

int abs(int);
unsigned int func_80086C84(void);
void func_80030484(Segment *, int);
void func_800305DC(Segment *);
void func_80022CAC(Segment *);
int func_8002F9BC(int, int, int, int, int);
void func_800302F4(Bridge *, int);
short func_80053598(Pos2);
int func_8005480C(int, int, int, int);
void func_80054DD0(int, int);
void func_80054EF4(int);

static inline int fixed_mul(int a, int b) {
    int low;

    __asm__ volatile("mult %1, %2\n\tmflo %0\n\tmfhi $3\n\tsrl %0, %0, 12\n\tsll $3, $3, 20\n\tor %0, %0, $3"
                     : "=&r"(low)
                     : "r"(a), "r"(b)
                     : "$3");
    return low;
}

static inline int sine_lookup(unsigned short *angle) {
    int out;

    __asm__ volatile("andi $8, %1, 0x4000\n\tandi $9, %1, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, %1, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(out)
                     : "r"(*angle)
                     : "$8", "$9");
    return out;
}

static inline int cosine_lookup(unsigned short *angle) {
    int out;

    __asm__ volatile("addu $10, %1, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $10, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(out)
                     : "r"(*angle)
                     : "$8", "$9", "$10");
    return out;
}

void func_8003077C(Bridge *bridge_arg, int *finished) {
    Bridge *bridge = bridge_arg;
    Segment *seg;
    Segment *next;
    int alive;
    int travel;
    int span;
    int target;
    int speed;
    short volume;
    int two;
    int trig;
    int period;
    Pos2 where;

    travel = 0;
    alive = 0;
    for (seg = bridge->segments; seg != 0; seg = seg->next) {
        if (seg->timer == -100 && seg->next != 0 && seg->next->timer != -100 &&
            func_80086C84() % 6 == 0) {
            func_80030484(seg->next, 1);
        }
        if (seg->timer != -100 && seg->next != 0 && seg->next->timer == -100 &&
            func_80086C84() % 6 == 0) {
            func_80030484(seg, 1);
        }
    }

    for (seg = bridge->segments; seg != 0; seg = seg->next) {
        if (seg->timer == 0) {
            seg->timer = -1;
            switch (seg->type) {
            case 1:
                func_80030484(seg, 1);
                break;
            case 3:
                break;
            case 4:
                func_800305DC(seg);
                break;
            }
        } else if (seg->timer > 0) {
            alive++;
        }
    }

    if (alive == 0) {
        seg = bridge->segments;
        while (seg != 0) {
            next = seg->next;
            func_80022CAC(seg);
            seg = next;
        }
        *finished = 1;
        return;
    }

    period = bridge->period << 12;
    switch (bridge->state) {
    case 0:
        switch (bridge->phase) {
        case 0:
            travel = func_8002F9BC(bridge->length - bridge->width, bridge->offset, period, 0, 0);
            target = bridge->offset + travel;
            span = bridge->length - bridge->width;
            if (span - 4096 < target) {
                bridge->phase = 3;
                bridge->timer = D_800D2FE0;
                target = span;
            }
            func_800302F4(bridge, target);
            break;
        case 1:
            travel = func_8002F9BC(bridge->length - bridge->width, bridge->offset, period, 0, 1);
            target = bridge->offset + travel;
            if (target < 4096) {
                bridge->phase = 2;
                bridge->timer = D_800D2FE0;
                target = 0;
            }
            func_800302F4(bridge, target);
            break;
        case 2:
            if (bridge->delay < D_800D2FE0 - bridge->timer) {
                bridge->phase = 0;
            }
            break;
        case 3:
            if (bridge->delay < D_800D2FE0 - bridge->timer) {
                bridge->phase = 1;
            }
            break;
        }
        break;
    case 1:
        switch (bridge->phase) {
        case 0:
            travel = func_8002F9BC(bridge->length - bridge->width, bridge->offset, period, 1, 0);
            target = bridge->offset + travel;
            if (bridge->length - bridge->width - 4096 < target) {
                bridge->phase = 2;
                bridge->timer = D_800D2FE0;
                target = 0;
            }
            func_800302F4(bridge, target);
            break;
        case 2:
            if (bridge->delay < D_800D2FE0 - bridge->timer) {
                bridge->phase = 0;
            }
            break;
        }
        break;
    }

    if (travel != 0) {
        trig = sine_lookup(&bridge->angle);
        two = 2;
        where.x = bridge->pos.x + fixed_mul(bridge->offset + bridge->width / two, trig >> 4);
        trig = cosine_lookup(&bridge->angle);
        where.z = bridge->pos.z + fixed_mul(bridge->offset + bridge->width / two, trig >> 4);
        speed = abs(travel / bridge->period);
        volume = fixed_mul(func_80053598(where), speed);
    } else {
        volume = 0;
    }

    if (volume != 0) {
        if (bridge->sound == 100) {
            bridge->sound = func_8005480C(49, volume, 0, 1);
        } else {
            func_80054DD0(bridge->sound, volume);
        }
    } else if (bridge->sound != 100) {
        func_80054EF4(bridge->sound);
        bridge->sound = 100;
    }
}

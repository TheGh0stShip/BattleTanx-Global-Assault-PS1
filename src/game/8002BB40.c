typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct Node {
    short id;
    short next;
    short kind;
    short pad06;
    struct Unit *unit;
} Node;

typedef struct Unit {
    char pad0[0x9C];
    int type;
} Unit;

typedef struct {
    void (*update)();
    void (*notify)(Node *, void *, int, void *, void *);
    void (*draw)();
} NodeClass;

typedef struct {
    char pad0[0x48];
    void *controlled;
} Player;

typedef struct {
    char pad0[0x5C];
    Player *player;
    char pad60[0x114 - 0x60];
} Waypoint;

typedef struct {
    Node *obj;
    int pad04;
    Vector pos;
    int pad14[4];
} Hit;

typedef struct {
    Vector pos;
    unsigned short heading;
    short pad0E;
    int kind;
    Waypoint *owner;
    int guided;
    int pad1C;
    int zero;
} HitInfo;

typedef struct {
    int result;
    int data[6];
} HitReply;

typedef struct {
    char pad0[8];
    Vector pos;
    int speed;
    int pitch;
    int climb;
    int turn;
    int timer;
    unsigned short heading;
    unsigned char kind;
    unsigned char flags;
    unsigned char owner;
    char pad2D[3];
    Node *target;
    void *sound0;
    void *sound1;
} Missile;

extern Waypoint D_800E3E68[];
extern NodeClass D_800D32F4[];
extern int D_800EC0F8[];
extern int D_800A6070;
extern int D_800DE30C;
extern short D_800C628C;
extern HitReply D_800BD910;
extern void func_800791C8(int, signed char *, signed char *, signed char *);
extern int func_8007906C(int, int, int *, int *, int *);
extern void func_800529E0(Waypoint *);
extern int func_8002B8EC(int, int);
extern int func_8002B7A0(int);
extern int func_8002B654(int);
extern int func_8008AD60(int);
extern int func_8008ACC0(int);
extern unsigned short func_80019D80(Vector *, Vector *, int, int, void *, Hit *);
extern void func_80053790(int, int, int);
extern void func_8006FDB0(int, Vector *, int, int);
extern void func_8006F224(void *, void *);
extern int func_800248CC(short, short);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline void approach(int *value, int target, int rate) {
    int cur = *value;
    int diff = target - cur;
    int step = fixed_mul(D_800DE30C, rate);

    if (diff >= -step) {
        if (diff <= step) {
            *value = target;
        } else {
            *value = cur + step;
        }
    } else {
        *value = cur - step;
    }
}

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

void func_8002BB40(Missile *obj, int *done) {
    Hit hit;
    Vector old;
    Vector next;
    HitInfo info;
    HitReply reply;
    Missile *m;
    Waypoint *w;
    int hit_something = 0;
    int show_blast = 1;
    signed char stick_y;
    signed char stick_x;
    signed char stick_x2;
    int button0 = 0;
    int button1 = 0;
    int button2 = 0;

    m = obj;
    func_800791C8(obj->owner, &stick_y, &stick_x, &stick_x2);
    if (obj->flags & 8) {
        obj->timer -= D_800DE30C;
        if (obj->timer > 0) {
            return;
        }
        func_800529E0(waypoint_get(obj->owner));
        *done = 1;
        return;
    }
    obj->timer -= D_800DE30C;
    if (obj->timer <= 0) {
        goto expired;
    }
    if (!(obj->flags & 1)) {
        return;
    }
    if (obj->flags & 4) {
        int turn;
        int pitch;
        int climb;
        int lo;
        int hi;
        int axis;

        if (func_8007906C(7, obj->owner, &button0, &button1, &button2) == 0) {
            Waypoint *pw = waypoint_get(obj->owner);

            m->flags &= ~4;
            if (pw->player->controlled == obj) {
                func_800529E0(pw);
            }
            goto move;
        }
        if ((D_800EC0F8[obj->owner] == 1 || D_800EC0F8[obj->owner] == 6) && D_800A6070 != 7) {
            axis = stick_x2;
        } else {
            axis = stick_x;
        }
        turn = -fixed_mul(640, func_8002B8EC(axis, 40));
        pitch = 0x4000 - fixed_mul(5462, func_8002B8EC(stick_y, 20));
        approach(&m->turn, turn, 128);
        approach(&m->pitch, pitch, 768);
        climb = m->pitch;
        lo = func_8002B7A0(m->pos.y);
        hi = func_8002B654(m->pos.y);
        if ((unsigned short)hi < climb) {
            climb = (unsigned short)hi;
        } else if (climb < (unsigned short)lo) {
            climb = (unsigned short)lo;
        }
        approach(&m->climb, climb, 768);
        m->heading += fixed_mul(D_800DE30C, m->turn);
    } else {
        approach(&obj->turn, 0, 128);
        approach(&m->pitch, 0x4000, 768);
        m->heading += fixed_mul(D_800DE30C, m->turn);
    }
move:
    {
        int dist = fixed_mul(D_800DE30C, fixed_mul(func_8008AD60(m->pitch >> 4), m->speed));

        next.x = m->pos.x + fixed_mul(func_8008AD60(m->heading >> 4), dist);
        next.z = m->pos.z + fixed_mul(func_8008ACC0(m->heading >> 4), dist);
        next.y = m->pos.y + fixed_mul(func_8008ACC0(m->pitch >> 4), m->speed);
        if (next.y > 0x1F4000) {
            next.y = 0x1F4000;
        } else if (next.y < 0xA000) {
            next.y = 0xA000;
        }
    }
    old.x = m->pos.x;
    old.y = m->pos.y;
    old.z = m->pos.z;
    D_800C628C = 1;
    if (func_80019D80(&m->pos, &next, 0x64940B, 0, 0, &hit) != 0) {
        if (m->target != 0 && hit.obj == m->target) {
            hit_something = 0;
            goto check;
        }
        if (hit.obj != 0) {
            reply = D_800BD910;
            info.pos.x = hit.pos.x;
            info.pos.y = hit.pos.y;
            info.pos.z = hit.pos.z;
            info.heading = m->heading;
            info.kind = m->kind;
            info.owner = waypoint_get(m->owner);
            info.guided = m->flags & 4;
            info.zero = 0;
            if (D_800D32F4[hit.obj->kind].notify != 0 && hit.obj->kind != -1) {
                D_800D32F4[hit.obj->kind].notify(hit.obj, m, 0, &info, &reply);
            }
            switch ((unsigned int)reply.result) {
            case 5:
                hit_something = 1;
                break;
            case 3:
                hit_something = 1;
                show_blast = 0;
                break;
            case 1:
                hit_something = 1;
                break;
            }
        } else {
            hit_something = 1;
        }
        m->target = 0;
    } else if (m->target == 0 || m->target->kind != 4 || m->target->unit->type != 11) {
        m->target = 0;
    }
check:
    if (hit_something) {
        w = waypoint_get(m->owner);
        if (show_blast) {
            func_80053790(11, m->pos.x, m->pos.z);
            func_8006FDB0(4, &old, 0, 0);
        }
        if (w->player->controlled == obj) {
            m->timer = 0x1E000;
            m->flags |= 8;
        } else {
            *done = 1;
        }
        if (m->sound0 != 0) {
            func_8006F224(m->sound0, m);
        }
        if (m->sound1 != 0) {
            func_8006F224(m->sound1, m);
        }
        return;
    }
    if (func_800248CC(fixed_to_int(next.x) >> 2, fixed_to_int(next.z) >> 2) == 0 || next.y <= 0) {
        w = waypoint_get(m->owner);
        func_80053790(11, m->pos.x, m->pos.z);
        goto finish;
    }
    m->pos.x = next.x;
    m->pos.z = next.z;
    m->pos.y = next.y;
    return;
expired:
    w = waypoint_get(obj->owner);
finish:
    *done = 1;
    if (m->sound0 != 0) {
        func_8006F224(m->sound0, m);
    }
    if (m->sound1 != 0) {
        func_8006F224(m->sound1, m);
    }
    if (w->player->controlled == obj) {
        func_800529E0(w);
    }
}

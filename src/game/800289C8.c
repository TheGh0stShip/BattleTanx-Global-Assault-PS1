typedef struct NodeMsg NodeMsg;
typedef struct Matrix Matrix;
typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    short id;
} Ident;

typedef struct {
    Ident *ident;
    char pad4[4];
    Vector pos;
    char pad14[0xB4 - 0x14];
    void *attacker;
    char padB8[0x218 - 0xB8];
    int status;
} Tank;

typedef struct {
    short id;
    short next;
    short kind;
} Node;

typedef struct {
    void (*update)();
    void (*notify)(Node *, void *, int, NodeMsg *, Matrix *);
    void (*draw)();
} NodeClass;

typedef struct {
    unsigned short turn;
    char pad2[2];
    int reload;
    int damage;
    int speed;
    char pad10[4];
    int weapon;
    char pad18[0x3C - 0x18];
    Vector muzzle;
    char pad48[4];
    unsigned short limit;
    char pad4E[0x54 - 0x4E];
} Kind;

typedef struct {
    char pad0[0xC];
    int team;
    char pad10[0x94 - 0x10];
    int scale;
    char pad98[0x114 - 0x98];
} Waypoint;

typedef struct {
    char pad0[6];
    unsigned char flags;
    unsigned char cooldown;
    Vector pos;
    unsigned short angle;
    unsigned short base;
    unsigned char los;
    unsigned char state;
    unsigned char mode;
    unsigned char kind;
    char pad1C;
    unsigned char owner;
    char pad1E[2];
    int target_id;
    unsigned short handle;
    char pad26[2];
    int timer;
    int last_fire;
    char pad30[4];
    Tank *target;
    int health;
    Node *node;
} Turret;

struct Matrix {
    short m[3][3];
    int t[3];
};

struct NodeMsg {
    int a;
    int b;
    Matrix mat;
    unsigned char flag;
    char pad29[0x58 - 0x29];
};

typedef struct {
    Ident *obj;
    int pad[8];
} Hit;

extern Kind D_800A44D4[];
extern Waypoint D_800E3E68[];
extern NodeClass D_800D32F4[];
extern int D_800D2FE0;
extern int D_800DE30C;
extern short D_800C628C;
extern unsigned char D_800AED58;
extern void func_8008A65C(Matrix *, Vector *, Vector *);
extern void func_80015F64(int, int, int);
extern void func_80053790(int, int, int);
extern void func_8001B094(int);
extern unsigned int func_80086C84(void);
extern Tank *func_800283E8(Vector *, int);
extern int func_8008AE30(int, int);
extern int func_8008AD60(int);
extern int func_8008ACC0(int);
extern int func_80047B7C(int, int);
extern void func_8008AA48(void *, int, int);
extern unsigned short func_80019D80(Vector *, Vector *, int, int, void *, Hit *);
extern void func_80038DB0(Vector *, int *, void *, int, int, int, void *, int, Waypoint *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int fixed_mul2(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult\t%2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
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

static inline Waypoint *waypoint_get_initial(int index, int null_value) {
    if (index == 127) {
        return (Waypoint *)null_value;
    }
    return &D_800E3E68[index];
}

static inline void identity_matrix(Matrix *m) {
    __asm__ volatile("li $8, 4096\n\tsw $8, 0(%0)\n\tsw $0, 4(%0)\n\tsw $8, 8(%0)\n\tsw $0, 12(%0)\n\tsw $8, 16(%0)\n\tsw $0, 20(%0)\n\tsw $0, 24(%0)\n\tsw $0, 28(%0)"
                     : : "r"(m) : "$8", "memory");
}

void func_800289C8(Turret *arg0, int *arg1) {
    int *done = arg1;
    Turret *obj = arg0;
    Kind *kind;
    int scale;
    int aim = 0;
    int turning;
    Vector pos;
    Tank *t;

    __asm__("move $21,$zero" : "=r"(turning));

    kind = &D_800A44D4[obj->kind];
    scale = waypoint_get_initial(obj->owner, turning)->scale;
    if (obj->node != 0 && obj->node->id == 0) {
        goto dead;
    }
    if (obj->cooldown != 0) {
        obj->cooldown--;
    }
    if (obj->node != 0) {
        {
        Vector *out = &pos;
        NodeMsg msg;
        NodeClass *cls;

        identity_matrix(&msg.mat);
        msg.a = 0;
        msg.b = 0;
        msg.flag = 0;
        if (D_800D32F4[obj->node->kind].notify != 0 && obj->node->kind != -1) {
            D_800D32F4[obj->node->kind].notify(obj->node, obj, 1, &msg, &msg.mat);
        }
        func_8008A65C(&msg.mat, &obj->pos, out);
        func_80015F64(obj->handle, *(short *)&out->x, *(short *)&out->z);
        }
    } else {
        pos = obj->pos;
    }
    if (obj->health <= 0) {
        if (!(obj->flags & 2)) {
            func_80053790(10, pos.x, pos.x);
        }
    dead:
        if (obj->handle != 0xFFFF) {
            func_8001B094(obj->handle);
        }
        *done = 1;
        return;
    }
    switch (obj->state) {
    case 0:
        if ((func_80086C84() & 0xF) == 0) {
            Tank *found = func_800283E8(&pos, waypoint_get(obj->owner)->team);

            obj->target = found;
            if (found != 0) {
                int id = found->ident->id;

                obj->state = 1;
                obj->cooldown = 0;
                obj->target_id = id;
            }
        }
        break;
    case 1:
        if ((func_80086C84() & 0xF) == 0) {
            t = func_800283E8(&pos, waypoint_get(obj->owner)->team);
            if (t == 0) {
                obj->state = 0;
                obj->target = 0;
                break;
            }
            if (obj->target != t) {
                obj->cooldown = 0;
            }
            obj->target = t;
            obj->target_id = t->ident->id;
        } else if (!(obj->target->status & 1) || obj->target->ident->id != obj->target_id) {
            obj->state = 0;
            break;
        }
        turning = 1;
        aim = (func_8008AE30(obj->target->pos.x - pos.x, obj->target->pos.z - pos.z) & 0xFFF) << 4;
        break;
    case 3:
        turning = 1;
        aim = obj->angle + 5462;
        if (D_800D2FE0 > obj->timer) {
            obj->state = 0;
        }
        break;
    }
    if (turning) {
        int diff = func_80047B7C(obj->angle, aim & 0xFFFF);
        int step = fixed_mul(fixed_mul(scale, kind->turn), D_800DE30C);

        if (obj->state == 3) {
            step *= 3;
        }
        if (diff < -step) {
            obj->angle -= step;
        } else if (diff <= step) {
            obj->angle = aim;
        } else {
            obj->angle += step;
        }
        if (kind->limit != 0) {
            int lim;
            int off;

            off = func_80047B7C(obj->base, obj->angle);
            lim = kind->limit;
            if (off < -lim) {
                obj->angle = obj->base - lim;
            } else if (lim < off) {
                obj->angle = obj->base + lim;
            }
        }
    }
    if ((obj->mode == 2 || obj->mode == 0) && turning) {
        int a = aim & 0xFFFF;

        if ((func_80047B7C(obj->angle, a) >= 0 ? func_80047B7C(obj->angle, a) : -func_80047B7C(obj->angle, a)) < 512
            && obj->target != 0 && fixed_mul(scale, kind->reload) < D_800D2FE0 - obj->last_fire) {
            Vector start;
            Vector muzzle;
            int vel[2];
            unsigned char buf[8];
            int s;
            int c;
            int sp;
            int sound;
            int idx;
            int mx;
            int mz;

            func_8008AA48(buf, 0, 8);
            idx = obj->angle >> 4;
            s = func_8008AD60(idx);
            c = func_8008ACC0(idx);
            if (obj->cooldown != 0 && obj->los == 0) {
                return;
            }
            muzzle = kind->muzzle;
            if (obj->flags & 1) {
                muzzle.x = -muzzle.x;
            }
            obj->flags ^= 1;
            mx = muzzle.x;
            mz = muzzle.z;
            start.x = pos.x + fixed_mul(c, mx) + fixed_mul(s, mz);
            start.z = pos.z - fixed_mul(s, mx) + fixed_mul(c, mz);
            start.y = pos.y + muzzle.y;
            if (obj->cooldown == 0) {
                Hit hit;
                Vector to;
                int ok;

                to = obj->target->pos;
                to.y = start.y;
                D_800C628C = 1;
                if (func_80019D80(&start, &to, 0x64940B, 0, obj, &hit) == 0 || hit.obj != obj->target->ident) {
                    ok = 0;
                } else {
                    ok = 1;
                }
                obj->los = ok;
                obj->cooldown = 16;
                if (!obj->los) {
                    return;
                }
            }
            sp = scale * kind->speed;
            vel[0] = fixed_mul2(sp, s);
            vel[1] = fixed_mul(sp, c);
            switch ((unsigned int)kind->weapon) {
            case 0:
                sound = 4;
                break;
            case 1:
                sound = 41;
                break;
            case 2:
                sound = 25;
                break;
            default:
                sound = 0;
                break;
            }
            func_80053790(sound, pos.x, pos.z);
            if (D_800AED58 & 1) {
                func_80038DB0(&start, vel, buf, obj->angle, (fixed_mul(scale, kind->damage) * 2) & 0xFF, kind->weapon, obj, 0,
                              waypoint_get(obj->owner));
            } else {
                func_80038DB0(&start, vel, buf, obj->angle, fixed_mul(scale, kind->damage) & 0xFF, kind->weapon, obj, 0,
                              waypoint_get(obj->owner));
            }
            if (obj->target != 0) {
                obj->target->attacker = obj;
            }
            obj->last_fire = D_800D2FE0;
        }
    }
}

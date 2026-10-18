typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    int x;
    int z;
} Point;
typedef struct {
    int x;
    int y;
    int z;
    unsigned short part;
    char padE[2];
    int source;
    int damage;
    int scaled;
    char pad1C[4];
    int effect;
} Hit;
typedef struct {
    char pad0[4];
    union {
        unsigned short kind;
        short signed_kind;
    } u;
    char pad6[2];
    void *owner;
} Object;
typedef struct {
    char pad0[8];
    int x;
    int y;
    int z;
    char pad14[0x34 - 0x14];
    char model[0x9C - 0x34];
    int type;
    char padA0[0x214 - 0xA0];
    int armor;
} Tank;
extern int func_80022814();
extern void func_8001F224(void *, int, int, Point *, Point *);
extern void func_80043D30(void *, int *);
extern void func_800400C0(Tank *, int, int, int, Hit *, int, int *);
extern void func_8003FB68(Tank *, int, int, int);

static inline void set_point(Point *p, int x, int z) {
    p->x = x;
    p->z = z;
}

static inline void apply_hit(Tank *tank, Hit *hit, int *out) {
    if (func_80022814() != 0) {
        func_800400C0(tank, hit->source, hit->scaled != 0 ? hit->damage : 0, 0, hit, hit->part, out + 1);
    } else {
        func_800400C0(tank, hit->source, hit->damage, 0, hit, hit->part, out + 1);
    }
}

static inline void apply_damage(Tank *tank, Hit *hit) {
    if (func_80022814() != 0) {
        func_8003FB68(tank, hit->source, hit->scaled != 0 ? hit->damage : 0, 0);
    } else {
        func_8003FB68(tank, hit->source, hit->damage, 0);
    }
}

void func_80046DD8(Tank *tank, Object *obj, Hit *hit, int *out) {
    Point from;
    Point to;
    void *owner;
    int effect;
    int x;
    int z;

    switch ((short)(obj->u.kind - 4)) {
    case 0:
        *out = 1;
        owner = obj->owner;
        if (hit != 0 && tank != 0 && (effect = hit->effect) != 0) {
            x = tank->x;
            z = tank->z;
            from.x = x;
            from.z = z;
            set_point(&to, hit->x, hit->z);
            func_8001F224(tank->model, effect, 2048, &from, &to);
            *out = 8;
            func_80043D30(owner, out);
        }
        return;
    case 8:
    case 35:
    case 36:
    case 48:
        apply_hit(tank, hit, out);
        if (tank->armor > 0 && (obj->u.signed_kind == 40 || obj->u.signed_kind == 52)) {
            *out = 5;
        } else {
            *out = 1;
        }
        return;
    case 3:
        apply_hit(tank, hit, out);
        *out = 1;
        return;
    case 63:
        if (tank->type == 8) {
            return;
        }
        apply_damage(tank, hit);
        *out = 1;
        return;
    }
    if (hit->source > 0 && tank != 0) {
        apply_damage(tank, hit);
    }
    *out = 1;
}

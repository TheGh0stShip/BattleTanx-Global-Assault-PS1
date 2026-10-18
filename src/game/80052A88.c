typedef struct {
    int x;
    int z;
    unsigned short heading;
    short pad;
} Spawn;
typedef struct {
    int x;
    int y;
    int z;
    unsigned short heading;
    unsigned char team;
    unsigned char kind;
    void *position;
    int zero14;
    int four;
    int model;
    int two;
    int extra0;
    int extra1;
    int zero2C;
} Desc;
typedef struct {
    int id;
} Spawned;
typedef struct {
    char pad0[7];
    unsigned char team;
    char pad8[0xA4 - 8];
    unsigned char kind;
    char padA5[0xA8 - 0xA5];
    Spawn *spawns;
    char padAC[0xB0 - 0xAC];
    int model;
    int extra0;
    int extra1;
} Unit;
extern int func_8004305C(void *, int, int, unsigned short, int, int, int);
extern Spawned *func_8003EEF8(Desc *);
extern void func_80052A24(Unit *, int);

static inline void set_extra(Desc *d, Unit *u) {
    d->extra0 = u->extra0;
    d->extra1 = u->extra1;
}

int func_80052A88(Unit *unit, void *position, int plain) {
    Desc desc;
    Spawn *spawn;
    int found = 0;
    int i;

    for (i = 0; i < 5; i++) {
        spawn = &unit->spawns[i];
        if (func_8004305C(position, spawn->x, spawn->z, spawn->heading, 1, 0, 0) != 0) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return -1;
    }
    desc.zero14 = 0;
    desc.position = position;
    desc.four = 4;
    desc.model = unit->model;
    desc.heading = spawn->heading;
    desc.x = spawn->x;
    desc.y = 0;
    desc.z = spawn->z;
    desc.two = 2;
    desc.team = unit->team;
    desc.kind = unit->kind;
    if (plain != 0) {
        desc.extra1 = 0;
        desc.extra0 = 0;
    } else {
        set_extra(&desc, unit);
    }
    desc.zero2C = 0;
    func_80052A24(unit, func_8003EEF8(&desc)->id);
    return 0;
}

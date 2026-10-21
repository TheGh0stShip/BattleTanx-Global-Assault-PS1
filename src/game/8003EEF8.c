typedef struct { int x, y, z; } Vector;

typedef struct {
    char pad0[4];
    short model_a;
    short model_b;
    short model_c;
    short model_d;
    short model_e;
    short model_f;
    char pad10[0x14 - 0x10];
    char physics[0x30 - 0x14];
    unsigned short health;
    char pad32[0x34 - 0x32];
    int ammo_a;
    int ammo_b;
    int low_a;
    int low_b;
    char pad44[0x4C - 0x44];
    unsigned short shells;
    char pad4E[0xD0 - 0x4E];
} Vehicle;

typedef struct Tank Tank;

typedef struct Team {
    char pad0[6];
    unsigned char options;
    char pad7[0x78 - 7];
    Tank *list[3];
    unsigned char count[8];
    int health_scale;
    int mass_scale;
    char pad94[0xA4 - 0x94];
    unsigned char color;
    char padA5[0x114 - 0xA5];
} Team;

typedef struct {
    Vector pos;
    unsigned short heading;
    signed char team;
    char padF;
    int type;
    int kind;
    char pad18[0x20 - 0x18];
    int flags;
    int pickup_a;
    int pickup_b;
    int script;
} SpawnInfo;

typedef struct {
    char pad0[8];
    Tank *tank;
} Shadow;

typedef struct {
    int m[8];
} Mat;

struct Tank {
    Shadow *shadow;
    Tank *next;
    Vector pos;
    Vector last;
    Vector vel;
    unsigned short heading;
    unsigned short pad2E;
    unsigned short turret;
    unsigned short pad32;
    char body[0x40 - 0x34];
    int mass;
    char pad44[0x98 - 0x44];
    int team;
    int type;
    int kind;
    int fA4;
    char padA8[0x208 - 0xA8];
    Team *owner;
    int max_health;
    int health;
    int f214;
    int status;
    char pad21C[0x22C - 0x21C];
    unsigned short ammo[17];
    unsigned short pad24E;
    int weapon[2];
    int last_fire[2];
    int f260;
    int f264;
    char pad268[0x27E - 0x268];
    short f27E;
    int f280;
    int f284;
    int f288;
    char pad28C[0x290 - 0x28C];
    unsigned char tint[3];
    char pad293;
    int f294;
    char pad298[0x2A4 - 0x298];
    int script;
    char pad2A8[0x2B4 - 0x2A8];
    int f2B4;
    short model;
    char pad2BA[0x2DC - 0x2BA];
    Mat rot;
    unsigned char color;
    char pad2FD[0x300 - 0x2FD];
    int ammo_a;
    int ammo_b;
    char counter_a[0x3E8 - 0x308];
    char counter_b[0x57C - 0x3E8];
    int f57C;
    int shake;
    int shake_state;
    int shake_time;
    int f58C;
    int f590;
    int f594;
};

typedef struct {
    char data[20];
} Cell;

typedef struct {
    char pad0[336];
    Cell cells[1];
} Arena;

typedef struct {
    Arena *arena;
    char pad4[0x10 - 4];
    int count;
    char pad14[0x39 - 0x14];
    unsigned char slot[4];
} World;

extern Team D_800E3E68[];
extern Tank D_800DE33C[];
extern unsigned short D_800DE338;
extern Vehicle D_800A4EF4[];
extern World D_800D2FE4;
extern int D_800D2FE0;
extern unsigned char D_800AED49;
extern unsigned char D_800AED4A;
extern short D_800ABA68[];
extern Shadow *func_8002380C(int, int);
extern void func_8007A344(void *, int);
extern void func_8007A1DC(Tank *);
extern void func_8001EEE4(void *, void *);
extern short func_800162F0(Shadow *, int, int, int, int, int, int, int, int, int, int, int);
extern void func_8008AC90(void *, int);
extern int func_8001EF94(void *, void *, int *);
extern int func_80022814(void);
extern void func_80040620(Tank *, int, int);
extern void func_80063BF8(void *, int, int);
extern void func_80063C68(void *, int, int);
extern void func_80063D8C(int *, int *, int);
extern void func_80047BB8(Tank *, int, SpawnInfo *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int to_int(int v) {
    if (v >= 0)
        return v >> 12;
    return -(-v >> 12);
}

static inline Vehicle *vehicle_info(int type) {
    return &D_800A4EF4[type];
}

static inline void copy_vector(Vector *dst, Vector *src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

static inline void set_health(Tank *t, int health) {
    int was_low;
    int is_low;

    was_low = t->health < t->max_health >> 1;
    t->health = health;
    is_low = health < t->max_health >> 1;
    if (was_low != is_low) {
        if (is_low) {
            t->ammo_a = vehicle_info(t->type)->low_b;
            t->ammo_b = vehicle_info(t->type)->low_a;
        } else {
            t->ammo_a = vehicle_info(t->type)->ammo_b;
            t->ammo_b = vehicle_info(t->type)->ammo_a;
        }
        func_8007A344(t->counter_a, t->ammo_a);
        func_8007A344(t->counter_b, t->ammo_b);
        func_8007A1DC(t);
    }
}

static inline Team *team_ptr(int team) {
    if (team == 127)
        return 0;
    return &D_800E3E68[team];
}

static inline void set_player_flag(unsigned int player, short value) {
    if (player < 2) {
        D_800ABA68[player] = value;
    }
}

static inline void init_matrix(Mat *m) {
    __asm__ volatile("li $8, 4096\n\tsw $8, 0(%0)\n\tsw $0, 4(%0)\n\tsw $8, 8(%0)\n\tsw $0, 12(%0)\n\tsw $8, 16(%0)\n\tsw $0, 20(%0)\n\tsw $0, 24(%0)\n\tsw $0, 28(%0)"
                     :
                     : "r"(m)
                     : "$8", "memory");
}

Tank *func_8003EEF8(SpawnInfo *info) {
    Tank *tank;
    Team *team;
    Shadow *shadow;
    int i;
    int tmp[2];

    tank = 0;
    team = team_ptr(info->team);
    for (i = 0; i < 16; i++) {
        if (!(D_800DE33C[i].status & 1)) {
            tank = &D_800DE33C[i];
            break;
        }
    }
    if (tank == 0) {
        return 0;
    }
    shadow = func_8002380C(4, 12);
    if (shadow == 0) {
        return 0;
    }
    shadow->tank = tank;
    tank->shadow = shadow;
    copy_vector(&tank->pos, &info->pos);
    copy_vector(&tank->last, &info->pos);
    tank->vel.x = tank->vel.y = tank->vel.z = 0;
    tank->heading = info->heading;
    tank->turret = 0;
    tank->team = info->team;
    tank->type = info->type;
    tank->kind = info->kind;
    tank->max_health = to_int(fixed_mul(team->health_scale, D_800A4EF4[info->type].health << 12));
    tank->status = info->flags | 1;
    D_800DE338++;
    tank->health = 0;
    set_health(tank, tank->max_health);
    tank->owner = team_ptr(tank->team);
    tank->next = team->list[tank->kind];
    team->list[tank->kind] = tank;
    team->count[tank->kind]++;
    tank->ammo_a = D_800A4EF4[tank->type].ammo_b;
    tank->ammo_b = D_800A4EF4[tank->type].ammo_a;
    tank->color = tank->owner->color;
    tank->f27E = 0;
    tank->f280 = 0;
    tank->f284 = 0;
    tank->f288 = 0;
    tank->tint[0] = 100;
    tank->tint[1] = 100;
    tank->tint[2] = 100;
    func_8001EEE4(tank->body, D_800A4EF4[((volatile Tank *)tank)->type].physics);
    tank->mass = fixed_mul(team->mass_scale, tank->mass);
    tank->model = func_800162F0(shadow, (short)(to_int(tank->pos.x) >> 2), (short)(to_int(tank->pos.z) >> 2), 0,
                                D_800A4EF4[tank->type].model_a, D_800A4EF4[tank->type].model_b,
                                D_800A4EF4[tank->type].model_c, D_800A4EF4[tank->type].model_d,
                                D_800A4EF4[tank->type].model_e, D_800A4EF4[tank->type].model_f,
                                tank->heading, 8);
    func_8008AC90(tank->ammo, 34);
    tank->ammo[1] = D_800A4EF4[tank->type].shells;
    tank->weapon[0] = 1;
    tank->weapon[1] = 0;
    tank->last_fire[0] = 0;
    tank->last_fire[1] = 0;
    if (tank->kind == 2) {
        tmp[0] = tank->pos.x;
        tmp[1] = tank->pos.z;
        tank->heading = func_8001EF94(tank->body, &D_800D2FE4.arena->cells[D_800D2FE4.slot[tank->team]], tmp);
        tank->pos.x = tmp[0];
        tank->pos.z = tmp[1];
        tank->heading += 0x4000;
    }
    tank->fA4 = 0;
    tank->script = info->script;
    if (tank->status & 0x40) {
        D_800D2FE4.count++;
    }
    if (tank->kind == 0 && (tank->owner->options & 8)) {
        tank->ammo[16] = 1;
        if (tank->weapon[1] == 0) {
            tank->weapon[1] = 16;
        }
    }
    tank->f294 = -1000;
    tank->f2B4 = -1000;
    tank->f264 = 0;
    if (D_800AED49 & 1) {
        if (!(D_800AED4A & 1)) {
            tank->ammo[8] = 10;
            tank->ammo[2] = 10;
            tank->ammo[9] = 15;
            tank->ammo[4] = 10;
            tank->ammo[3] = 10;
            tank->ammo[10] = 10;
            tank->ammo[7] = 1;
            tank->ammo[13] = 10;
            tank->ammo[6] = 20;
            tank->ammo[12] = 1000;
            tank->ammo[14] = 20;
            tank->ammo[11] = 10;
            tank->ammo[15] = 5;
            tank->ammo[16] = 1;
        } else {
            tank->ammo[8] = 99;
            tank->ammo[12] = 1000;
            tank->ammo[2] = 99;
            tank->ammo[9] = 99;
            tank->ammo[4] = 99;
            tank->ammo[3] = 99;
            tank->ammo[10] = 99;
            tank->ammo[7] = 99;
            tank->ammo[13] = 99;
            tank->ammo[6] = 99;
            tank->ammo[14] = 99;
            tank->ammo[11] = 99;
            tank->ammo[15] = 99;
            tank->ammo[16] = 1;
        }
        tank->weapon[1] = 4;
        if (tank->status & 2) {
            set_player_flag((unsigned short)tank->team, 1);
            tank->status |= 0x1000;
        }
    }
    tank->f214 = 0;
    if (!func_80022814()) {
        func_80040620(tank, info->pickup_a, 0);
        func_80040620(tank, info->pickup_b, 0);
    }
    if (tank->status & 2) {
        func_80063BF8(&tank->ammo[tank->weapon[0]], (unsigned short)tank->team, tank->type);
        func_80063C68(tank->weapon[1] ? &tank->ammo[tank->weapon[1]] : 0, (unsigned short)tank->team, tank->weapon[1]);
        func_80063D8C(&tank->max_health, &tank->health, (unsigned short)tank->team);
        if (!(D_800AED49 & 1)) {
            set_player_flag((unsigned short)tank->team, 0);
        }
    }
    func_80047BB8(tank, 0, info);
    init_matrix(&tank->rot);
    tank->shake_state = 0;
    if (!func_80022814() && tank->kind == 0 && D_800D2FE0 != 0) {
        tank->shake_state = 1;
        tank->f57C = 0x5A000;
        tank->shake_time = -1000;
        tank->status |= 0x80;
    }
    tank->f58C = 0;
    tank->f594 = D_800D2FE0;
    return tank;
}

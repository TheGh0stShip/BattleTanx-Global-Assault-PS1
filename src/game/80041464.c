typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;

typedef struct Matrix {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct Point2 {
    int x;
    int z;
} Point2;

typedef struct Quad {
    Point2 p[4];
} Quad;

typedef struct Emitter {
    Vector pos;
    int size;
} Emitter;

typedef struct Zone {
    Quad bounds;
    int pad[2];
} Zone;

typedef struct EmitterList {
    int count;
    Emitter *items;
} EmitterList;

typedef struct Owner {
    char pad0[0x6];
    unsigned char flags;
    char pad7[0x81];
    int scale;
} Owner;

typedef struct VehicleInfo {
    char pad0[0x10];
    unsigned int flags;
    char pad14[0x20];
    int turret_full;
    int hull_full;
    int turret_damaged;
    int hull_damaged;
    char pad44[0xC];
    int shot_kind;
    int shot_speed;
    char pad58[0x8];
    int shot_damage;
    int shot_sound;
    Vector muzzle;
    char pad74[0xC];
    Vector pivot;
    char pad8C[0x18];
    EmitterList *emitters;
    char padA8[0x28];
} VehicleInfo;

typedef struct Tank {
    int id;
    char pad4[0x4];
    Vector pos;
    char pad14[0x18];
    unsigned short heading;
    char pad2E[0x2];
    unsigned short turret;
    char pad32[0x66];
    int player;
    int type;
    char padA0[0x168];
    Owner *owner;
    int armor_max;
    int armor;
    char pad214[0x4];
    unsigned int flags;
    char pad21C[0x4];
    int push_x;
    char pad224[0x4];
    int push_z;
    char pad22C[0x38];
    int boost_timer;
    char pad268[0x4];
    int drop_time;
    int drop_count;
    char pad274[0x20];
    int fire_time;
    char pad298[0x20];
    unsigned short slot;
    char pad2BA[0x22];
    char link[0x24];
    int hull_model;
    int turret_model;
    char hull[0xE0];
    char turret_obj[0x194];
    int shield_level;
    int shield_rate;
    unsigned int shield_state;
    int shield_time;
    int power;
} Tank;

extern VehicleInfo D_800A4EF4[];
extern unsigned char D_800AED52;
extern unsigned char D_800AED54;
extern unsigned char D_800AED59;
extern char D_800A4D1C[];
extern int D_800AE954;
extern int D_800D2FE0;
extern Zone D_800C62B0[];

void func_8008A65C(Matrix *, Vector *, Vector *);
void func_80040EE8(Vector *, Tank *, Vector *);
int func_80023B8C(Vector *, int, int, int, int, int);
void func_8006FDB0(int, Vector *, int, int);
int func_8002C584(Vector *, int, int, int, int, int, int);
void func_80054DF8(Tank *, int);
void func_800735C8(Vector *, int, int, int, int);
void func_8006C334(int, int, Vector *, Vector *, int, int, int, int);
void func_8008634C(int, char *, int);
void func_80036890(Vector *, Vector *, int, int, int, int, int, int);
void func_80038DB0(Vector *, int *, int *, int, int, int, int, int, Owner *);
unsigned int func_80086C84(void);
int func_8008ACC0(int);
int func_8008AD60(int);
void func_8002B4C8(Vector *, int, int, int, int, int, Owner *);
void func_80053E14(Tank *);
void func_8001B094(int);
void func_80074B24(int, Tank *, void *);
void func_8002E078(Vector *, Vector *, int, int, int, int, Owner *);
void func_8007A344(void *, int);
void func_8007A1DC(Tank *);
void func_80016FF4(Zone *, Quad *);
int func_8001EA3C(Point2 *);
void func_80053790(int, int, int);
void func_80027F38(Vector *, int, int);
void func_80028720(int, Vector *, int, int, int);
void func_80063018(int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int sine_lookup(int angle) {
    int value;

    __asm__ volatile("andi $8, %1, 0x4000\n\tandi $9, %1, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, %1, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9");
    return value;
}

static inline int cosine_lookup(int angle) {
    int value;

    __asm__ volatile("addiu $10, %1, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $10, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll %0, $9, 1"
                     : "=r"(value)
                     : "r"(angle)
                     : "$8", "$9", "$10");
    return value;
}

static inline void matrix_identity_y(Matrix *m, unsigned short *angle) {
    __asm__ volatile("lhu $11, %1\n\tli $8, 4096\n\tsw $8, 8(%0)\n\tsh $0, 2(%0)\n\tsh $0, 6(%0)\n\tsh $0, 14(%0)\n\tsw $0, 20(%0)\n\tsw $0, 24(%0)\n\tsw $0, 28(%0)"
                     :
                     : "r"(m), "m"(*angle)
                     : "$8", "memory");
}

static inline void matrix_rot_y_sin(Matrix *m) {
    __asm__ volatile("andi $8, $11, 0x4000\n\tandi $9, $11, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $11, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll $10, $9, 1\n\tsra $10, $10, 4\n\tsh $10, 4(%0)\n\tneg $10, $10\n\tsh $10, 12(%0)"
                     :
                     : "r"(m)
                     : "$8", "$9", "$10", "memory");
}

static inline void matrix_rot_y_cos(Matrix *m) {
    __asm__ volatile("addiu $10, $11, 0x4000\n\tandi $8, $10, 0x4000\n\tandi $9, $10, 0x3fff\n\tbeqz $8, 1f\n\tnop\n\tli $8, 16383\n\tsub $9, $8, $9\n1:\n\tandi $9, $9, 0x3ffe\n\t.set noat\n\tlui $1, 0x800b\n\taddu $1, $1, $9\n\tlhu $9, 3820($1)\n\t.set at\n\tandi $8, $10, 0x8000\n\tbeqz $8, 2f\n\tnop\n\tneg $9, $9\n2:\n\tsll $10, $9, 1\n\tsra $10, $10, 4\n\tsh $10, 0(%0)\n\tsh $10, 16(%0)"
                     :
                     : "r"(m)
                     : "$8", "$9", "$10", "memory");
}

static inline int fixed_int(int x) {
    if (x >= 0) {
        return x >> 12;
    }
    return -(-x >> 12);
}

static inline int Tank_Scale(Tank *t, int k) {
    return t->owner->scale * k;
}

static inline int Tank_Damage(Tank *t, int k) {
    return fixed_int(t->owner->scale * k);
}

static inline unsigned char Tank_Powered(Tank *t) {
    return t->power > 0;
}

static inline void Tank_Recoil(Tank *t, int k) {
    unsigned short angle;
    int r;

    angle = t->heading + t->turret - 0x8000;
    r = (((func_80086C84() >> 16) * 3277) >> 16) + 1638;
    k = fixed_mul(r, k);
    t->push_x += fixed_mul(func_8008ACC0(angle >> 4), k);
    t->push_z -= fixed_mul(func_8008AD60(angle >> 4), k);
}

static inline void Tank_SetArmorModels(Tank *t, int damaged) {
    if (damaged) {
        t->hull_model = D_800A4EF4[t->type].hull_damaged;
        t->turret_model = D_800A4EF4[t->type].turret_damaged;
    } else {
        t->hull_model = D_800A4EF4[t->type].hull_full;
        t->turret_model = D_800A4EF4[t->type].turret_full;
    }
    func_8007A344(t->hull, t->hull_model);
    func_8007A344(t->turret_obj, t->turret_model);
    func_8007A1DC(t);
}

static inline void Tank_AddArmor(Tank *t, int add) {
    int old;
    int was;
    int now;

    old = t->armor;
    was = old < t->armor_max >> 1;
    now = old + add;
    t->armor = now;
    now = now < t->armor_max >> 1;
    if (was != now) {
        Tank_SetArmorModels(t, now);
    }
}

static inline void Tank_FireShell(Tank *t, Vector *pos, unsigned char big) {
    Vector dir;
    int a;
    int size;

    a = t->heading + t->turret;
    dir.x = sine_lookup(a) >> 4;
    dir.z = cosine_lookup(a) >> 4;
    dir.y = 0;
    size = 50;
    if (big) {
        size = 100;
    }
    func_80036890(pos, &dir, (unsigned short)a, (unsigned char)t->player, size, t->id, (unsigned char)t->flags & 2, 3);
    func_80054DF8(t, 25);
}

static inline void Tank_FireShellAt(Tank *t, int a, int big, Vector *pos) {
    Vector dir;
    int size;

    dir.x = sine_lookup(a) >> 4;
    dir.z = cosine_lookup(a) >> 4;
    dir.y = 0;
    size = 50;
    if ((unsigned char)big) {
        size = 100;
    }
    func_80036890(pos, &dir, (unsigned short)a, (unsigned char)t->player, size, t->id, (unsigned char)t->flags & 2, 3);
    func_80054DF8(t, 25);
}

static inline void Tank_FireLaser(Tank *t, Vector *pos, int k, int mode) {
    unsigned char big;
    int dmg;

    big = Tank_Powered(t);
    dmg = Tank_Damage(t, k);
    if (big) {
        dmg <<= 1;
    }
    if (func_8002C584(pos, 0x78000, (unsigned short)(t->heading + t->turret), (unsigned char)dmg,
                      (unsigned char)t->player, t->id, mode)) {
        func_80054DF8(t, 27);
    }
}

static inline void Tank_LaserShot(Tank *t, Vector *pos, unsigned char dmg, int mode) {
    if (func_8002C584(pos, 0x78000, (unsigned short)(t->heading + t->turret), dmg,
                      (unsigned char)t->player, t->id, mode)) {
        func_80054DF8(t, 27);
    }
}

static inline void Tank_FireMissile(Tank *t, Vector *pos) {
    int kind;

    t->fire_time = D_800D2FE0;
    kind = 3;
    if (t->power > 0) {
        kind = 6;
    }
    func_800735C8(pos, (unsigned short)(t->heading + t->turret), kind, t->player, t->id);
}

int func_80041464(Tank *t, int weapon)
{
    Vector pos;
    Vector flash;
    Matrix m;
    int vel[2];
    int acc[2];
    int boost;

    boost = 0;
    if (t->flags & 2) {
        boost = D_800AED52 & 1;
    }
    flash = D_800A4EF4[t->type].muzzle;
    if ((D_800A4EF4[t->type].flags & 2) && (t->flags & 4)) {
        flash.x = -flash.x;
    }
    matrix_identity_y(&m, &t->turret);
    matrix_rot_y_sin(&m);
    matrix_rot_y_cos(&m);
    func_8008A65C(&m, &flash, &flash);
    flash.x += D_800A4EF4[t->type].pivot.x;
    flash.y += D_800A4EF4[t->type].pivot.y;
    flash.z += D_800A4EF4[t->type].pivot.z;
    func_80040EE8(&pos, t, &D_800A4EF4[t->type].muzzle);
    t->flags ^= 4;

    switch (weapon) {
    case 1:
        switch (t->type) {
        case 12:
            if (t->power <= 0) {
                func_8006FDB0(12, &t->pos, 0, func_80023B8C(&t->pos, t->player, 175, 97, 0, 2500));
            } else {
                func_8006FDB0(10, &t->pos, 0, func_80023B8C(&t->pos, t->player, 255, 97, 0, 9000));
            }
            return 0;
        case 10:
        case 11:
            Tank_FireLaser(t, &pos, 35, 0);
            break;
        case 8:
            Tank_FireMissile(t, &pos);
            func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
            return 0;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 14: {
            int angle;
            int speed;
            unsigned char dmg;
            int d;

            angle = t->heading + t->turret;
            speed = D_800A4EF4[t->type].shot_speed;
            vel[0] = fixed_mul(sine_lookup(angle) >> 4, speed);
            vel[1] = fixed_mul(cosine_lookup(angle) >> 4, speed);
            acc[1] = 0;
            acc[0] = 0;
            if (D_800A4EF4[t->type].shot_sound != -1) {
                func_80054DF8(t, (unsigned char)D_800A4EF4[t->type].shot_sound);
            }
            if (t->flags & 2) {
                func_8008634C(t->player, D_800A4D1C, 0);
            }
            d = fixed_int(t->owner->scale * D_800A4EF4[t->type].shot_damage) << boost;
            if (t->power > 0) {
                d <<= 1;
            }
            dmg = d;
            if ((D_800AED54 & 1) && (t->flags & 2)) {
                unsigned char big;

                big = 0;
                if (t->power > 0 || boost) {
                    big = 1;
                }
                Tank_FireShell(t, &pos, big);
            } else {
                func_80038DB0(&pos, vel, acc, (unsigned short)angle, dmg, D_800A4EF4[t->type].shot_kind, t->id,
                              (unsigned char)t->flags & 2, t->owner);
                if ((D_800AED59 & 1) && (t->flags & 2)) {
                    vel[0] = fixed_mul(-4096, vel[0]);
                    vel[1] = fixed_mul(-4096, vel[1]);
                    func_80038DB0(&pos, vel, acc, (angle + 0x8000) & 0xFFFF, dmg,
                                  D_800A4EF4[t->type].shot_kind, t->id, (unsigned char)t->flags & 2, t->owner);
                }
            }
            Tank_Recoil(t, (D_800A4EF4[t->type].shot_damage << 11) / 40);
            func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
            return 0;
        }
        case 13: {
            int dmg;

            dmg = Tank_Damage(t, 60);
            if (t->power > 0) {
                dmg <<= 1;
            }
            func_8002B4C8(&pos, (unsigned short)(t->heading + t->turret), dmg, 1, t->id, 1, t->owner);
            func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
            return 0;
        }
        default:
            return 0;
        }
        func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
        return 0;
    case 8: {
        unsigned int flags;

        flags = t->flags;
        if (flags & 8) {
            return -1;
        }
        t->flags = flags | 8;
        t->drop_count = 0;
        t->drop_time = D_800D2FE0;
        func_80053E14(t);
        func_8001B094(t->slot);
        t->slot = 0xFFFF;
        func_80074B24(2, t, t->link);
        return 0;
    }
    case 2: {
        int acc[2];
        int vel[2];
        int side[2];
        unsigned char power;
        unsigned short angle;
        int a;

        power = Tank_Damage(t, 30);
        angle = (unsigned short)(t->heading + t->turret);
        a = angle >> 4;
        vel[0] = fixed_mul(0x118000, func_8008AD60(a));
        vel[1] = fixed_mul(0x118000, func_8008ACC0(a));
        side[0] = vel[1];
        side[1] = -vel[0];
        acc[0] = 0;
        acc[1] = 0;
        func_80038DB0(&pos, vel, acc, angle, power, 2, t->id, 1, t->owner);
        vel[0] += side[0] / 10;
        vel[1] += side[1] / 10;
        acc[0] = -side[0] / 200;
        acc[1] = -side[1] / 200;
        func_80038DB0(&pos, vel, acc, angle, power, 2, t->id, 1, t->owner);
        vel[0] -= side[0] / 5;
        vel[1] -= side[1] / 5;
        acc[0] = side[0] / 200;
        acc[1] = side[1] / 200;
        func_80038DB0(&pos, vel, acc, angle, power, 2, t->id, 1, t->owner);
        func_80054DF8(t, 27);
        Tank_Recoil(t, 2048);
        func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
        return 0;
    }
    case 9: {
        Vector vel;
        int dmg;
        unsigned char power;
        unsigned short angle;
        int a;

        dmg = Tank_Scale(t, 30);
        angle = (unsigned short)(t->heading + t->turret);
        power = fixed_int(dmg);
        a = angle >> 4;
        vel.x = fixed_mul(func_8008AD60(a), 0x118000);
        vel.z = fixed_mul(func_8008ACC0(a), 0x118000);
        vel.y = 0;
        func_8002E078(&pos, &vel, angle, power, 1, t->id, t->owner);
        func_8002E078(&pos, &vel, angle, power, 1, t->id, t->owner);
        func_8002E078(&pos, &vel, angle, power, 1, t->id, t->owner);
        func_80054DF8(t, 32);
        if (t->power > 0) {
            func_8002E078(&pos, &vel, angle, power, 1, t->id, t->owner);
            func_8002E078(&pos, &vel, angle, power, 1, t->id, t->owner);
        }
        func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
        return 0;
    }
    case 4: {
        Vector *p;
        unsigned char big;
        int dmg;

        p = &pos;
        big = Tank_Powered(t);
        dmg = Tank_Damage(t, 100);
        if (big) {
            dmg <<= 1;
        }
        Tank_LaserShot(t, p, dmg, 1);
        func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
        return 0;
    }
    case 3: {
        int angle;

        angle = t->heading + t->turret;
        Tank_FireShellAt(t, angle, Tank_Powered(t), &pos);
        func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
        return 0;
    }
    case 7:
        func_8002B4C8(&pos, (unsigned short)(t->heading + t->turret), Tank_Damage(t, 250), 3, t->id, 1,
                      t->owner);
        func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
        return 0;
    case 14: {
        int dmg;

        dmg = Tank_Damage(t, 40);
        if (t->power <= 0) {
            func_8002B4C8(&pos, (unsigned short)(t->heading + t->turret), dmg, 0, t->id, 1, t->owner);
        } else {
            dmg <<= 1;
            func_8002B4C8(&pos, (unsigned short)(t->heading + t->turret), dmg, 1, t->id, 1, t->owner);
        }
        func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
        return 0;
    }
    case 10: {
        int i;

        if (t->boost_timer != 0) {
            return -1;
        }
        t->boost_timer = D_800D2FE0 + 180;
        for (i = 0; i < D_800A4EF4[t->type].emitters->count; i++) {
            func_8006C334(t->id, 11, &D_800A4EF4[t->type].emitters->items[i].pos,
                          &D_800A4EF4[t->type].emitters->items[i].pos, 0,
                          D_800A4EF4[t->type].emitters->items[i].size, 0x1000, 0x5A000);
        }
        return 0;
    }
    case 11:
        if (t->armor >= t->armor_max) {
            return -1;
        }
        Tank_AddArmor(t, 30);
        if (t->armor > t->armor_max) {
            t->armor = t->armor_max;
        }
        func_80054DF8(t, 23);
        return 0;
    case 13: {
        unsigned int state;

        state = t->shield_state;
        if (state == 0) {
            t->shield_state = 2;
            t->shield_rate = 0x28000;
            func_80054DF8(t, 6);
            t->shield_level = 0x1C2000;
            t->shield_time = D_800D2FE0;
            func_80074B24(0, t, t->link);
            return 0;
        }
        if (state < 4) {
            t->shield_level += 0x1C2000;
        }
        break;
    }
    case 6: {
        Quad q;
        Point2 c;
        Vector p;

        func_80016FF4(&D_800C62B0[t->slot], &q);
        c.x = p.x = (q.p[3].x + q.p[0].x) >> 1;
        c.z = p.z = (q.p[3].z + q.p[0].z) >> 1;
        p.y = func_8001EA3C(&c);
        func_80053790(26, p.x, p.z);
        func_80027F38(&p, 0, t->player);
        return 0;
    }
    case 15: {
        Vector p;
        Quad q;
        unsigned short a;

        a = t->heading + t->turret;
        func_80016FF4(&D_800C62B0[t->slot], &q);
        a = (unsigned short)a >> 4;
        p.x = ((q.p[3].x + q.p[0].x) >> 1) + fixed_mul(-0x1F4000, func_8008AD60(a));
        p.z = ((q.p[3].z + q.p[0].z) >> 1) + fixed_mul(-0x1F4000, func_8008ACC0(a));
        p.y = t->pos.y;
        func_80028720(0, &p, (unsigned short)(t->heading + 0x8000), (unsigned char)t->player, 0);
        func_80054DF8(t, 33);
        return 0;
    }
    case 12:
        t->fire_time = D_800D2FE0;
        func_800735C8(&pos, (unsigned short)(t->heading + t->turret), 3, t->player, t->id);
        func_8006C334(t->id, 9, &flash, &flash, 0, 0x4000, 0x1000, 0x100);
        return 0;
    case 16: {
        Vector p;

        p.x = t->pos.x;
        p.y = t->pos.y + 0xC8000;
        p.z = t->pos.z;
        func_8006FDB0(14, &p, 0, func_80023B8C(&p, t->player, 100, 3, 1, 5000));
        t->owner->flags &= ~8;
        func_80054DF8(t, 8);
        func_80063018((unsigned short)t->player, D_800AE954, 45);
        break;
    }
    }
    return 0;
}

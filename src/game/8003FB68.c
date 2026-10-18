typedef struct { char pad[0x34]; int ammo_a; int ammo_b; int low_a; int low_b; char pad2[0xD0 - 0x44]; } Vehicle;
typedef struct { char pad[7]; unsigned char rank; char pad2[4]; int team; } Attacker;
typedef struct { char pad[0xC]; int team; } Owner;
typedef struct {
    char pad0[0x98];
    int player;
    int type;
    char pad1[0x17C - 0xA0];
    int state;
    char pad2[0x208 - 0x180];
    Owner *owner;
    int max_health;
    int health;
    int f214;
    unsigned int status;
    char pad3[0x300 - 0x21C];
    int ammo_a;
    int ammo_b;
    char counter_a[0x3E8 - 0x308];
    char counter_b[0x580 - 0x3E8];
    int shake;
    int shake_state;
    int shake_time;
} Tank;
extern Vehicle D_800A4EF4[];
extern unsigned char D_800AED48;
extern unsigned char D_800AED51;
extern unsigned char D_800AED55;
extern int D_800D2FE0;
extern char D_800A4D08[];
extern char D_800A4CF8[];
extern char D_800A4CEC[];
extern char D_800A4CE0[];
extern char D_800A4CD8[];
extern void func_800531D4(Attacker *, int);
extern void func_8007A344(void *, int);
extern void func_8007A1DC(Tank *);
extern void func_80054DF8(Tank *, int);
extern void func_8008634C(int, char *, int);
extern void func_8003F82C(Tank *, int, int);

static inline Vehicle *vehicle_info(int type)
{
    return &D_800A4EF4[type];
}

static inline void set_health(Tank *t, int health)
{
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

void func_8003FB68(Tank *t, int damage, Attacker *attacker)
{
    if (t->status == 0) {
        return;
    }
    if ((D_800AED48 & 1) && (t->status & 2)) {
        return;
    }
    if (t->state == 26) {
        return;
    }
    if ((D_800AED51 & 1) && (t->status & 2)) {
        damage >>= 1;
    }
    if (damage == 0) {
        damage = 1;
    }
    if ((D_800AED55 & 1) && (t->status & 2)) {
        damage <<= 1;
    }
    if (attacker != 0 && attacker->team == t->owner->team) {
        func_800531D4(attacker, 7);
    }
    set_health(t, t->health - damage);
    switch (t->shake_state) {
    case 1:
        t->shake_state = 3;
        t->shake = 0x14000;
        t->shake_time = D_800D2FE0;
        break;
    case 3:
        t->shake = 0x14000;
        t->shake_time = D_800D2FE0;
        break;
    }
    if (t->health <= 0) {
        t->health = 1;
        func_80054DF8(t, 42);
        if (t->status & 2) {
            func_8008634C(t->player, D_800A4D08, 0);
        }
        func_8003F82C(t, attacker != 0 ? attacker->rank : 127, (damage > 500) * 2);
        return;
    }
    if (t->status & 2) {
        if (damage > 40) {
            func_8008634C(t->player, D_800A4CF8, 0);
        } else if (damage > 20) {
            func_8008634C(t->player, D_800A4CEC, 0);
        } else if (damage > 5) {
            func_8008634C(t->player, D_800A4CE0, 0);
        } else if (damage > 0) {
            func_8008634C(t->player, D_800A4CD8, 0);
        }
    }
}

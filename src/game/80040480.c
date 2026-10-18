typedef struct { char pad[0x34]; int ammo_a; int ammo_b; char pad2[0xD0 - 0x3C]; } Vehicle;
typedef struct { char pad[0xC]; int team; } Owner;
typedef struct {
    char pad0[0x9C];
    int type;
    char pad1[0x208 - 0xA0];
    Owner *owner;
    int f20C;
    int f210;
    int f214;
    unsigned int status;
    char pad2[0x300 - 0x21C];
    int ammo_a;
    int ammo_b;
    char counter_a[0x3E8 - 0x308];
    char counter_b[0x598 - 0x3E8];
} Tank;
extern Vehicle D_800A4EF4[];
extern Tank D_800DE33C[];
extern void func_8007A344(void *, int);
extern void func_8007A1DC(Tank *);

static inline Vehicle *vehicle_info(int type)
{
    return &D_800A4EF4[type];
}

static inline void refill_tank(Tank *t)
{
    t->f210 = t->f20C;
    t->ammo_a = vehicle_info(t->type)->ammo_b;
    t->ammo_b = vehicle_info(t->type)->ammo_a;
    func_8007A344(t->counter_a, t->ammo_a);
    func_8007A344(t->counter_b, t->ammo_b);
    func_8007A1DC(t);
}

void func_80040480(Tank *tank)
{
    Owner *owner;
    int team;
    Tank *t;
    int i;

    owner = tank->owner;
    team = owner->team;
    if (owner == 0) {
        refill_tank(tank);
        return;
    }
    for (i = 0; i < 16; i++) {
        t = &D_800DE33C[i];
        if (t->status & 1) {
            if (t->owner == owner) {
                refill_tank(t);
            } else if (team != 0 && t->owner->team == team) {
                refill_tank(t);
            }
        }
    }
}

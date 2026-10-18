typedef struct { short f0; unsigned short deaths; } TeamStats;
typedef struct Tank Tank;
typedef struct {
    char pad0[0xC];
    TeamStats *team;
    char pad1[0x78 - 0x10];
    Tank *lists[3];
    unsigned char counts[4];
    char pad2[0xD2 - 0x88];
    unsigned short losses;
} Owner;
typedef struct { char pad[0xC]; TeamStats *team; char pad2[0x114 - 0x10]; } Killer;
typedef struct { char pad[0xCA]; unsigned short points; char pad2[0xD0 - 0xCC]; } Vehicle;
typedef struct { char pad[4]; short kind; char pad2[0x27 - 6]; unsigned char count; } Carrier;
typedef struct { char pad[8]; int active; } Body;
struct Tank {
    Body *body;
    Tank *next;
    int x;
    int y;
    int z;
    char pad0[0x98 - 0x14];
    unsigned short player;
    char pad1[2];
    int type;
    int list;
    char pad2[0x208 - 0xA4];
    Owner *owner;
    char pad3[0x218 - 0x20C];
    unsigned int status;
    char pad4[0x2A4 - 0x21C];
    Carrier *carrier;
    char pad5[0x2B8 - 0x2A8];
    unsigned short voice;
};
typedef struct { char pad[0x10]; int alive; } Game;
extern Killer D_800E3E68[];
extern Vehicle D_800A4EF4[];
extern Game D_800D2FE4;
extern short D_800ABA68[];
extern unsigned short D_800DE338;
extern void func_80052984(int, int);
extern void func_800530E0(Killer *, int, int);
extern void func_80033A38(Tank *);
extern void func_80053790(int, int, int);
extern int func_800374F0(Tank *, int);
extern void func_8001B094(int);
extern void func_80063DB8(int);
extern void func_80052BE8(Owner *, Tank *);
extern void func_80053E14(Tank *);
extern void func_8004E2AC(Tank *, int);
extern void func_80047BB8(Tank *, int, int);

static inline void unlink_tank(Tank *t, int list)
{
    Tank **link;
    Tank *p;

    link = &t->owner->lists[list];
    while (*link != 0) {
        p = *link;
        if (p == t) {
            break;
        }
        link = &p->next;
    }
    *link = t->next;
    t->owner->counts[list]--;
    t->status &= ~1;
    t->body->active = 0;
    D_800DE338--;
    t->list = 3;
    func_80047BB8(t, 1, 0);
}

void func_8003F82C(Tank *t, int killer, unsigned int kind)
{
    Killer *k;
    int list;
    unsigned int player;

    if (!(t->status & 1)) {
        return;
    }
    if (killer != 127) {
        k = &D_800E3E68[killer];
        if (k->team != t->owner->team) {
            func_80052984(killer, 1);
            func_800530E0(k, D_800A4EF4[t->type].points, 0);
        }
    }
    t->owner->team->deaths++;
    t->owner->losses++;
    func_80033A38(t);
    if (t->status & 0x40) {
        D_800D2FE4.alive--;
    }
    switch (kind) {
    case 0:
    case 1:
        if (t->type == 1) {
            func_80053790(7, t->x, t->z);
        } else {
            func_80053790(43, t->x, t->z);
        }
        func_800374F0(t, 0);
        break;
    case 2:
        if (t->type == 1) {
            func_80053790(7, t->x, t->z);
        } else {
            func_80053790(42, t->x, t->z);
        }
        func_800374F0(t, 1);
        break;
    default:
        func_8001B094(t->voice);
        t->voice = 0xFFFF;
        break;
    }
    if (t->status & 2) {
        func_80063DB8(t->player);
        player = t->player;
        if (player < 2) {
            D_800ABA68[player] = 0;
        }
    }
    if ((t->status & 2) || t->list == 0) {
        func_80052BE8(t->owner, t);
        func_80053E14(t);
    }
    if (t->carrier != 0 && t->carrier->kind == 14) {
        t->carrier->count--;
    }
    list = t->list;
    func_8004E2AC(t, 29);
    unlink_tank(t, list);
}

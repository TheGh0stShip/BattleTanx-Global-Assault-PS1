typedef struct Team {
    char pad0[0xC];
    int score;
} Team;

typedef struct Owner {
    char pad0[0xC];
    Team *team;
    char pad10[0x64];
    unsigned short kills;
} Owner;

typedef struct VehicleInfo {
    char pad0[0x34];
    int turret_full;
    int hull_full;
    int turret_damaged;
    int hull_damaged;
    char pad44[0x8];
    int ammo;
    char pad50[0x80];
} VehicleInfo;

typedef struct Tank {
    char pad0[0x98];
    unsigned short player;
    char pad9A[0x2];
    int type;
    int unkA0;
    char padA4[0x164];
    Owner *owner;
    int armor_max;
    int armor;
    int unk214;
    unsigned int flags;
    char pad21C[0x10];
    unsigned short counts[20];
    int selected;
    char pad258[0xA8];
    int hull_model;
    int turret_model;
    char hull[0xE0];
    char turret[0x1A4];
    int unk58C;
} Tank;

extern VehicleInfo D_800A4EF4[];
extern short D_800ABA68[];
extern int D_800EAD4C, D_800EAE50, D_800EAD78, D_800EAF24, D_800EAD60, D_800EAD7C;
extern int D_800EAC44, D_800EAEF0, D_800EAE60, D_800EAC2C, D_800EAD40, D_800EAD70;
extern int D_800EAE30, D_800EADE8, D_800EAF28, D_800EAC84, D_800EAF20, D_800EAF34;
extern int D_800EAE58, D_800EAC98;
void func_80063C68(unsigned short *, unsigned short, int);
void func_80063018(unsigned short, int, int);
void func_8007A344(void *, int);
void func_8007A1DC(Tank *);
void func_80054DF8(Tank *, int);
void func_80040480(Tank *);

static inline void Tank_AddItem(Tank *t, int idx, int n)
{
    t->counts[idx] += n;
    if (t->selected == 0) {
        t->selected = idx;
        if (t->flags & 2) {
            func_80063C68(&t->counts[idx], t->player, idx);
        }
    }
}

static inline void Tank_SetArmorModels(Tank *t, int damaged)
{
    if (damaged) {
        t->hull_model = D_800A4EF4[t->type].hull_damaged;
        t->turret_model = D_800A4EF4[t->type].turret_damaged;
    } else {
        t->hull_model = D_800A4EF4[t->type].hull_full;
        t->turret_model = D_800A4EF4[t->type].turret_full;
    }
    func_8007A344(t->hull, t->hull_model);
    func_8007A344(t->turret, t->turret_model);
    func_8007A1DC(t);
}

static inline void Tank_AddArmor(Tank *t, int add)
{
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

void func_80040620(Tank *t, int kind, unsigned short show)
{
    int msg;
    int add;
    unsigned short player;

    msg = 0;
    switch (kind) {
    case 1:
        Tank_AddItem(t, 2, 5);
        msg = D_800EAD4C;
        break;
    case 2:
        Tank_AddItem(t, 3, 5);
        msg = D_800EAE50;
        break;
    case 3:
        Tank_AddItem(t, 4, 5);
        msg = D_800EAD78;
        break;
    case 5:
        Tank_AddItem(t, 7, 1);
        msg = D_800EAF24;
        break;
    case 6:
        Tank_AddItem(t, 6, 5);
        msg = D_800EAD60;
        break;
    case 12:
        Tank_AddItem(t, 10, 5);
        msg = D_800EAD7C;
        break;
    case 4:
        Tank_AddItem(t, 15, 2);
        msg = D_800EAC44;
        break;
    case 14:
        Tank_AddItem(t, 12, 100);
        msg = D_800EAEF0;
        break;
    case 15:
        Tank_AddItem(t, 13, 2);
        msg = D_800EAE60;
        break;
    case 16:
        Tank_AddItem(t, 14, 5);
        msg = D_800EAC2C;
        break;
    case 17:
        t->owner->team->score += 5;
        msg = D_800EAD40;
        t->owner->kills += 5;
        break;
    case 18:
        if ((t->flags & 2) || t->unkA0 == 0) {
            player = t->player;
            if (player < 2) {
                D_800ABA68[player] = 1;
            }
            t->flags |= 0x1000;
        }
        msg = D_800EAD70;
        break;
    case 7:
        msg = D_800EAE30;
        if (t->armor == t->armor_max) {
            Tank_AddItem(t, 11, 1);
        } else {
            int repair;

            repair = 30;
            if (t->type == 2) {
                repair = 50;
            }
            Tank_AddArmor(t, repair);
            if (t->armor > t->armor_max) {
                t->armor = t->armor_max;
            }
            func_80054DF8(t, 23);
        }
        break;
    case 9:
        msg = D_800EADE8;
        Tank_AddItem(t, 8, 5);
        break;
    case 10:
        msg = D_800EAF28;
        Tank_AddItem(t, 9, 5);
        break;
    case 13:
        msg = D_800EAC84;
        t->unk214 = 100;
        break;
    case 11:
        msg = D_800EAF20;
        t->counts[1] += D_800A4EF4[t->type].ammo / 3;
        break;
    case 8:
        msg = D_800EAF34;
        t->counts[1] += D_800A4EF4[t->type].ammo / 6;
        add = 15;
        if (t->type == 2) {
            add = 25;
        }
        Tank_AddArmor(t, add);
        func_80054DF8(t, 23);
        if (t->armor > t->armor_max) {
            t->armor = t->armor_max;
        }
        break;
    case 19:
        msg = D_800EAE58;
        t->unk58C = 0x2A30000;
        break;
    case 20:
        func_80040480(t);
        msg = D_800EAC98;
        break;
    }
    if (show && msg) {
        func_80063018(t->player, msg, 45);
    }
}

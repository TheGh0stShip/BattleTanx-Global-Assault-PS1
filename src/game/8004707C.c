typedef struct Unit Unit;
typedef struct Force Force;
typedef struct {
    char pad0[4];
    short kind;
    char pad6[0x27 - 6];
    unsigned char users;
} Pickup;
struct Force {
    char pad0[7];
    unsigned char id;
    char pad8[0x78 - 8];
    Unit *heads[3];
    unsigned char counts[3];
};
struct Unit {
    char pad0[4];
    Unit *next;
    char pad8[0x94 - 8];
    void *reference;
    int force_id;
    int type;
    unsigned int list;
    char padA4[0x17C - 0xA4];
    int state;
    int flags;
    char pad184[0x208 - 0x184];
    Force *force;
    char pad20C[0x218 - 0x20C];
    int status;
    char pad21C[0x2A4 - 0x21C];
    Pickup *pickup;
};
extern void func_800505D8(Unit *, int, int, int);
extern void func_800531D4(Force *, int);
extern void func_80047BB8(Unit *, int, int);

void func_8004707C(Unit *unit, Force *force) {
    unsigned int list = unit->list;
    Force *old = unit->force;
    unsigned int slot = 0;
    Unit **link;
    int state;

    if (list == 0) {
        return;
    }
    if (unit->status & 0x40) {
        if (unit->type == 11) {
            unit->flags |= 0x10;
        } else {
            state = 6;
            if (unit->reference != 0) {
                state = unit->state;
            }
            unit->state = 27;
            func_800505D8(unit, 60, 0, state);
        }
        return;
    }
    func_800531D4(force, 1);
    if (unit->pickup != 0 && unit->pickup->kind == 14) {
        unit->pickup->users--;
        unit->pickup = 0;
    }
    func_80047BB8(unit, 2, 0);
    for (link = &old->heads[unit->list]; *link != 0; link = &(*link)->next) {
        if (*link == unit) {
            break;
        }
    }
    *link = unit->next;
    unit->force->counts[list]--;
    if (list < 3) {
        if (list != 0) {
            slot = 1;
        }
    }
    unit->next = force->heads[slot];
    force->heads[slot] = unit;
    unit->force = force;
    unit->list = slot;
    unit->force_id = force->id;
    unit->force->counts[slot]++;
    func_80047BB8(unit, 3, 0);
}

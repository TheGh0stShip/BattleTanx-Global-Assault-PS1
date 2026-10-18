typedef struct Unit Unit;
struct Unit {
    char pad0[4];
    Unit *next;
    char pad8[0x9C - 8];
    int type;
    char padA0[0x218 - 0xA0];
    int status;
};
typedef struct {
    char pad0[0xC8];
    unsigned short cost;
    char padCA[0xD0 - 0xCA];
} UnitType;
typedef struct {
    char pad0[0x78];
    Unit *list_a;
    char pad7C[4];
    Unit *list_b;
} Force;
extern UnitType D_800A4EF4[];

int func_80052E64(Force *force) {
    int total = 0;
    Unit *unit;

    for (unit = force->list_b; unit != 0; unit = unit->next) {
        if (unit->status & 2) {
            total += D_800A4EF4[unit->type].cost;
        }
    }
    for (unit = force->list_a; unit != 0; unit = unit->next) {
        if (unit->status & 2) {
            total += D_800A4EF4[unit->type].cost;
        }
    }
    return total;
}

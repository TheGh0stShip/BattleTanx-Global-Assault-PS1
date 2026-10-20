typedef struct Unit Unit;

struct Unit {
    int field00;
    Unit *next;
    unsigned char fields08[0xA0 - 8];
    unsigned int slot;
    unsigned char fieldsA4[0x218 - 0xA4];
    unsigned int flags;
};

typedef struct UnitSet {
    unsigned char fields00[0x78];
    Unit *heads[3];
} UnitSet;

typedef char Unit_size[(sizeof(Unit) == 0x21C) ? 1 : -1];
typedef char UnitSet_size[(sizeof(UnitSet) == 0x84) ? 1 : -1];

extern int func_80047688(Unit *);

static inline Unit *first_unit(UnitSet *set, Unit *unit) {
    unsigned int slot;
    Unit *result;

    if (unit == 0 || !(unit->flags & 1)) {
        result = set->heads[0];
        slot = 0;
    } else {
        slot = unit->slot;
        result = unit->next;
    }
    {
        register unsigned int initial asm("$6") = slot;
        asm("" : "+r"(initial));
        slot = initial;
    }
    while (result == 0 && slot < 2) {
        slot++;
        result = set->heads[slot];
    }
    return result;
}

static inline Unit *following_unit(UnitSet *set, Unit *unit) {
    unsigned int slot;
    Unit *result;

    if (unit == 0 || !(unit->flags & 1)) {
        result = set->heads[0];
        slot = 0;
    } else {
        slot = unit->slot;
        result = unit->next;
    }
    {
        register unsigned int initial asm("$5") = slot;
        asm("" : "+r"(initial));
        slot = initial;
    }
    while (result == 0 && slot < 2) {
        slot++;
        result = set->heads[slot];
    }
    return result;
}

Unit *func_80052F9C(UnitSet *set, Unit *after, unsigned int mask, int check) {
    Unit *unit = first_unit(set, after);

    while (unit != 0) {
        if ((unit->flags & mask) == mask &&
            (check == 0 || func_80047688(unit) != 0))
            break;
        unit = following_unit(set, unit);
    }
    return unit;
}

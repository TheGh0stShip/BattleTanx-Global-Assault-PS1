typedef struct {
    char pad0[0xC];
    int level;
} Info;
typedef struct {
    char pad0[8];
    int unlocked;
    Info *info;
    char pad10[0x54 - 0x10];
    int roster;
} Unit;
typedef struct {
    char pad0[0x54];
    int available;
} Session;
typedef struct {
    char pad0[0xC8];
    unsigned short required;
    char padCA[0xD0 - 0xCA];
} Vehicle;
typedef struct {
    int ids[5];
} Lineup;
extern unsigned char D_800AED4B;
extern unsigned char D_800AED4F;
extern Session *D_800D3024;
extern Vehicle D_800A4EF4[];
extern int func_80022814();
extern Lineup *func_80053338(int);

static inline int is_set(int mask, int bit) {
    return mask & (1 << bit);
}

int func_80052784(Unit *unit, int *ids, unsigned char *enabled) {
    int count = 0;
    int i;

    if (D_800AED4B & 1) {
        int mask = ~0x4800;

        for (i = 0; i < 15; i++) {
            if (is_set(mask, i)) {
                ids[count] = i;
                enabled[count] = 1;
                count++;
            }
        }
        return count;
    }
    if (func_80022814() != 0) {
        int mask = D_800D3024->available;

        if (D_800AED4F & 1) {
            mask |= 0x200;
        }
        for (i = 0; i < 15; i++) {
            if (is_set(mask, i)) {
                ids[count] = i;
                if (unit->info->level >= D_800A4EF4[i].required) {
                    enabled[count] = 1;
                } else {
                    enabled[count] = 0;
                }
                count++;
            }
        }
        return count;
    } else {
        int j = 0;
        Lineup *lineup = func_80053338(unit->roster);
        int k;

        for (k = 0; k < 5; k++) {
            if (count != 0) {
                for (j = 0; j < count; j++) {
                    if (lineup->ids[k] == ids[j]) {
                        break;
                    }
                }
            }
            if (j >= count) {
                ids[count] = lineup->ids[k];
                if (is_set(unit->unlocked, lineup->ids[count])) {
                    enabled[count] = 1;
                } else {
                    enabled[count] = 0;
                }
                count++;
            }
        }
        return count;
    }
}

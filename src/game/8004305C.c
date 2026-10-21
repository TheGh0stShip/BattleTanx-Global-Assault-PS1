typedef struct {
    char pad0[4];
    short ext[6];
    char pad10[0xD0 - 0x10];
} VehicleType;
typedef struct {
    int owner;
    char pad4[32];
} Found;
extern VehicleType D_800A4EF4[];
extern short D_800C628C;
extern int func_8002476C(int, int);
extern int func_800248CC(int, int);
extern int func_8001AED4(int, int, int, int, int, int, int, int, int, int, int, int);
extern unsigned short func_80017AAC(unsigned short, int, Found *, int, int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline int count_blockers(unsigned short box, int mask, int ignore) {
    Found found[8];
    int total;
    int count;
    int i;
    Found *f;

    if (ignore != 0) {
        D_800C628C = 0;
        total = (unsigned short)func_80017AAC(box, mask, found, 0, 0);
        count = total;
        for (i = 0; i < total; i++) {
            if (found[i].owner != ignore) {
                return count;
            }
            count--;
        }
        return 0;
    }
    D_800C628C = 0;
    count = func_80017AAC(box, mask, found, 0, 1);
    if (count != 0) {
        return count;
    }
    return 0;
}

int func_8004305C(int type, int x, int z, unsigned short heading, unsigned char strict, unsigned char check_map, int ignore) {
    unsigned short box;
    int mask;

    if (check_map) {
        if (func_8002476C((short)(fixed_to_int(x) >> 2), (short)(fixed_to_int(z) >> 2)) == 0) {
            return 0;
        }
        if (func_800248CC((short)(fixed_to_int(x) >> 2), (short)(fixed_to_int(z) >> 2)) == 0) {
            return 0;
        }
    }
    box = func_8001AED4(0, (short)(fixed_to_int(x) >> 2), (short)(fixed_to_int(z) >> 2), 0,
                        D_800A4EF4[type].ext[0], D_800A4EF4[type].ext[1], D_800A4EF4[type].ext[2],
                        D_800A4EF4[type].ext[3], D_800A4EF4[type].ext[4], D_800A4EF4[type].ext[5],
                        heading, 8);
    if (strict) {
        return count_blockers(box, 0x240008, ignore) == 0;
    }
    mask = 0x64510B;
    if (check_map) {
        mask = 0x164510B;
    }
    return count_blockers(box, mask, ignore) == 0;
}

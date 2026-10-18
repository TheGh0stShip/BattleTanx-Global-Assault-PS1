typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    char pad000[0x78];
    void *target;
    char pad07C[0x98];
} PoolEntry;

typedef struct {
    char pad000[0x98];
    u32 target_index;
    char pad09C[0x2D];
    u8 mode;
    char pad0CA[2];
    void *mode_object;
} Tank;

typedef struct {
    char pad000[0x218];
    u32 flags;
} ModeObject;

extern PoolEntry D_800E3E68[];

void func_8004E0FC(Tank *, void *, int, int);

void func_8004FC5C(Tank *tank) {
    PoolEntry *entry;

    if (tank->mode == 0 ||
        (tank->mode == 1 && (((ModeObject *)tank->mode_object)->flags & 3) != 3)) {
        if (tank->target_index == 127) {
            entry = 0;
        } else {
            entry = &D_800E3E68[tank->target_index];
        }
        if (entry->target != 0) {
            func_8004E0FC(tank, entry->target, 0x190000, 0);
        }
    }
}

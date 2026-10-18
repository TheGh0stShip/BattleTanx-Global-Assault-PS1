typedef unsigned int u32;

typedef struct {
    char pad000[0x10];
    u32 flags;
    char pad014[0xBC];
} VehicleDefinition;

typedef struct {
    char pad000[0x9C];
    u32 vehicle_type;
    char pad0A0[4];
    void *active_object;
    char pad0A8[0x154];
    int timer;
    char pad200[0x10];
    int deadline;
} Tank;

extern VehicleDefinition D_800A4EF4[];

void func_8004E2AC(Tank *, int);
void func_8004DD5C(Tank *);

void func_8004FD34(Tank *tank) {
    if (tank->active_object != 0) {
        func_8004E2AC(tank, 20);
    } else {
        int deadline;

        deadline = tank->deadline;
        if (tank->timer >= deadline &&
            (D_800A4EF4[tank->vehicle_type].flags & 1)) {
            func_8004E2AC(tank, 22);
        } else {
            func_8004DD5C(tank);
        }
    }
}

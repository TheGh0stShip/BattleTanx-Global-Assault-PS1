typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    short x;
    short y;
    short z;
} Angle;
typedef struct {
    int x;
    int z;
} Point2;
typedef struct {
    char pad0[4];
    short ext[6];
    char pad10[0xD0 - 0x10];
} VehicleType;
typedef struct {
    int flags;
    int owner;
    char pad8[40 - 8];
} Cell;
typedef struct {
    int id;
    char pad4[4];
    Vector position;
    char pad14[0x2C - 0x14];
    unsigned short heading;
    char pad2E[0x34 - 0x2E];
    char body[0x9C - 0x34];
    int type;
    char padA0[0x218 - 0xA0];
    int status;
    char pad21C[0x26C - 0x21C];
    int spawn_time;
    int spawn_state;
    char pad274[0x2B8 - 0x274];
    unsigned short cell;
    char pad2BA[0x2DC - 0x2BA];
    char effect[4];
} Vehicle;
extern int D_800D2FE0;
extern VehicleType D_800A4EF4[];
extern Cell D_800C62B0[];
extern unsigned int func_80086C84(void);
extern void func_800718A4(int, Vector *, Angle *, int, int);
extern void func_8004332C(Vehicle *, Point2 *, Point2 *);
extern int func_8004305C(int, int, int, unsigned short, unsigned char, unsigned char, int);
extern unsigned short func_800162F0(int, short, short, int, int, int, int, int, int, int, int, int);
extern void func_80074B24(int, Vehicle *, void *);
extern void func_80043454(Vehicle *);
extern void func_80054DF8(Vehicle *, int);
extern void func_8001E7A4(void *, unsigned short);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline short random_angle(void) {
    return ((int)(func_80086C84() >> 16) * 4097 >> 16) - 0x800;
}

static inline short random_lift(void) {
    return ((int)(func_80086C84() >> 16) * 2049 >> 16) + 0x800;
}

void func_800437A4(Vehicle *vehicle) {
    Vector pos;
    Angle angle;
    int elapsed;
    int placed;
    int x;
    int z;
    unsigned short heading;
    unsigned short cell;

    elapsed = D_800D2FE0 - vehicle->spawn_time;
    if (vehicle->spawn_state == 0 && elapsed >= 9) {
        vehicle->spawn_state = 1;
        pos.x = vehicle->position.x;
        pos.z = vehicle->position.z;
        pos.y = vehicle->position.y + D_800A4EF4[vehicle->type].ext[5] / 2;
    }
    if (vehicle->spawn_state == 1) {
        angle.x = random_angle();
        angle.y = random_lift();
        angle.z = random_angle();
        pos.x = vehicle->position.x;
        pos.y = vehicle->position.y + 0x80000;
        pos.z = vehicle->position.z;
        func_800718A4(7, &pos, &angle, 0xE00, 0);
        if (elapsed >= 47) {
            Point2 base;
            Point2 span;

            placed = 0;
            func_8004332C(vehicle, &base, &span);
            do {
                x = base.x + func_80086C84() % span.x;
                z = base.z + func_80086C84() % span.z;
                heading = func_80086C84() % 0xFFFF;
                if (func_8004305C(vehicle->type, x, z, heading, 0, 1, 0) != 0) {
                    vehicle->position.x = x;
                    vehicle->position.z = z;
                    vehicle->heading = heading;
                    cell = func_800162F0(0, fixed_to_int(vehicle->position.x) >> 2, fixed_to_int(vehicle->position.z) >> 2, 0,
                                                  D_800A4EF4[vehicle->type].ext[0], D_800A4EF4[vehicle->type].ext[1],
                                                  D_800A4EF4[vehicle->type].ext[2], D_800A4EF4[vehicle->type].ext[3],
                                                  D_800A4EF4[vehicle->type].ext[4], D_800A4EF4[vehicle->type].ext[5],
                                                  vehicle->heading, 8);
                    vehicle->cell = cell;
                    placed = 1;
                    D_800C62B0[cell].flags &= ~8;
                    D_800C62B0[vehicle->cell].flags |= 0x4000;
                    vehicle->spawn_state = 2;
                    func_80074B24(3, vehicle, vehicle->effect);
                    func_80043454(vehicle);
                }
            } while (!placed);
        }
    } else {
        Vector pos2;
        Angle angle2;

        angle2.x = random_angle();
        angle2.y = random_lift();
        angle2.z = random_angle();
        pos2.x = vehicle->position.x;
        pos2.y = vehicle->position.y + 0x80000;
        pos2.z = vehicle->position.z;
        func_800718A4(6, &pos2, &angle2, 0xE00, 0);
    }
    if (vehicle->spawn_state == 2 && elapsed >= 47) {
        vehicle->spawn_state = 3;
        func_80054DF8(vehicle, 39);
    }
    if (vehicle->spawn_state == 3 && elapsed >= 93) {
        D_800C62B0[vehicle->cell].owner = vehicle->id;
        D_800C62B0[vehicle->cell].flags &= 0x51A2280;
        D_800C62B0[vehicle->cell].flags |= 8;
        vehicle->status &= ~8;
        func_8001E7A4(vehicle->body, vehicle->cell);
    }
}

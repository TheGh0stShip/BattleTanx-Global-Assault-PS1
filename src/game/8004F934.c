typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[0x14];
    short x0;
    short z0;
    short x1;
    short z1;
} Map;
typedef struct {
    char pad0[0xA8];
    unsigned short radius;
    char padAA[0xD0 - 0xAA];
} VehicleType;
typedef struct {
    char pad0[0x9C];
    int type;
} Tank;
extern Map *D_800D2FE4;
extern VehicleType D_800A4EF4[];
extern short D_800C628C;
extern unsigned int func_80086C84(void);
extern unsigned short func_8001AED4(int, short, short, int, short, short, short, short, int, int, int, int);
extern unsigned short func_80017AAC(unsigned short, int, void *, int, int);
extern void func_8004E160(Tank *, Vector *, int, int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

int func_8004F934(Tank *tank) {
    int result;
    Map *map;
    short *bounds;
    unsigned short radius;
    unsigned short box;
    Vector point;
    char found[288];

    radius = D_800A4EF4[tank->type].radius;
    map = D_800D2FE4;
    bounds = &map->x0;
    point.x = bounds[2] - map->x0;
    point.x *= func_80086C84() & 0xFFF;
    point.x += map->x0;
    point.z = bounds[3] - bounds[1];
    point.z *= func_80086C84() & 0xFFF;
    point.z += bounds[1];
    result = 0;
    box = func_8001AED4(0, fixed_to_int(point.x) >> 2, fixed_to_int(point.z) >> 2, 0, -radius, radius, -radius,
                        radius, 0, 50, 0, 0);
    D_800C628C = 0;
    if (func_80017AAC(box, 0x104500F, found, 0, 1) == 0) {
        func_8004E160(tank, &point, 0x190000, 0);
        result = 1;
    }
    return result;
}

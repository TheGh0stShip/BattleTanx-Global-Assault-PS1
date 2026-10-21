typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;

typedef struct Wall {
    u8 pad00[6];
    u16 cell;
    Vector position;
    u16 angle;
    u8 waypoint;
    u8 pad17;
    short health;
    u8 pad1A[6];
    int model;
} Wall;

typedef struct Trigger {
    int x;
    int z;
    int scale;
    u8 pad0C[8];
    int damage;
} Trigger;

typedef struct Cell {
    u8 pad00[0x22];
    short radius;
    u8 pad24[4];
} Cell;

typedef struct Waypoint {
    u8 data[0x114];
} Waypoint;

extern Cell D_800C62B0[];
extern Waypoint D_800E3E68[];
extern int func_80024114(int value);
extern void func_80035948(int model, Vector *position, u16 angle,
                          int, int, int, int, int);
extern void func_800531D4(Waypoint *waypoint, int index);

static inline int fixed_to_int(int value)
{
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

void func_80031F20(Wall *wall, int elapsed, Trigger *trigger, u8 *handled)
{
    register int dx asm("$4") = fixed_to_int(wall->position.x - trigger->x);
    int dz = fixed_to_int(wall->position.z - trigger->z);
    register int dx_squared asm("$7") = dx * dx;
    register int dz_squared asm("$4") = dz * dz;
    int radius = D_800C62B0[wall->cell].radius;
    int range = trigger->scale;
    register int distance_squared asm("$3") = dx_squared + dz_squared;

    if (range + radius * radius < distance_squared) {
        return;
    }

    {
        int damage = func_80024114(trigger->damage);
        if (damage <= 0) {
            return;
        }
        if (wall->health > 0) {
            wall->health -= damage;
            if (wall->health <= 0) {
                func_80035948(wall->model, &wall->position, wall->angle,
                              0, 0, 0, 0, 0);
            }
        }
    }

    {
        int index = wall->waypoint;
        Waypoint *waypoint;
        if (index == 127) {
            waypoint = 0;
        } else {
            waypoint = &D_800E3E68[index];
        }
        func_800531D4(waypoint, 10);
    }
    *handled = 1;
}

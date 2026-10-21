typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Point;
typedef struct {
    int flags;
    int value;
    char pad08[12];
    unsigned short base;
    char pad16[10];
    unsigned short height;
    char pad22[6];
} Cell;
typedef struct { char pad[60]; int value; } Link;
typedef struct {
    int pad[2];
    int x;
    int y;
    int z;
    unsigned short heading;
    signed char hp;
    char pad17[5];
    int value;
    char pad20[8];
    int model;
    Link *link;
    int effect;
    unsigned char timer;
    unsigned char state;
    unsigned char rubble;
    unsigned char team;
    unsigned short cell;
} Obj;
extern Cell D_800C62B0[];
extern int D_800EAC1C;
extern int D_800D2FE8;
void func_80034DE4(int);
unsigned int func_80086C84(void);
void func_80035948(int, int *, int, int, int, int, int, int);
void func_8002E97C(Obj *);
void func_80016FF4(Cell *, Point *);
void func_8006C334(void *, int, Vector *, Vector *, int, int, int, int);
void func_80070D5C(Vector *, Vector *, int, int);
void func_80053790(int, int, int);
void func_8006FDB0(int, Vector *, int, int);
void func_80054A30(int);
int func_80023B8C(int *, int, int, int, int, int);
void func_8002EA70(Obj *);
void func_80061CC0(int, int, int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_8002EB68(Obj *obj, int *out) {
    Point corners[4];
    Cell *cell;
    int i;
    int height;

    if (obj->hp <= 0 && obj->effect != 0) {
        func_80034DE4(obj->effect);
        obj->effect = 0;
    }
    switch (obj->state) {
    case 0:
        if (obj->hp > 0) {
            break;
        }
        if (D_800EAC1C != 0 || (func_80086C84() & 7) != 0 || obj->team == 1 || obj->team == 2) {
            obj->state = 1;
            break;
        }
        {
        {
        Vector min;
        Vector max;
        Vector spot;
        Vector lo;
        Vector hi;
        Point *c;
        int i;
        int height;

        func_80035948(obj->model, &obj->x, obj->heading, 0, 0, 0, 0, 0);
        func_8002E97C(obj);
        __asm__ volatile("");
        c = corners;
        func_80016FF4(&D_800C62B0[obj->cell], c);
        cell = &D_800C62B0[obj->cell];
        height = (short)(cell->height + cell->base) << 14;
        min.x = min.z = 0xC350000;
        max.x = max.z = -0xC350000;
        for (i = 0; i < 4; i++) {
            int x = c->x;
            int z = c->z;

            if (x < min.x) {
                min.x = x;
            }
            if (max.x < x) {
                max.x = x;
            }
            if (z < min.z) {
                min.z = z;
            }
            if (max.z < z) {
                max.z = z;
            }
            c++;
        }
        min.y = 0;
        max.y = height;
        func_8006C334(0, 6, &min, &max, 0, 8192, 819, 0x19000);
        func_8006C334(0, 6, &min, &max, 0, 4096, 819, 0x19000);
        func_8006C334(0, 6, &min, &max, 0, 5461, 819, 0x19000);
        spot.x = min.x + func_80086C84() % (max.x - min.x);
        spot.z = min.z + func_80086C84() % (max.z - min.z);
        spot.y = 0;
        lo.x = spot.x - 0x10000;
        lo.y = 0x40000;
        lo.z = spot.z - 0x10000;
        hi.x = spot.x + 0x10000;
        hi.y = 0x60000;
        hi.z = spot.z + 0x10000;
        func_8006C334(0, 3, &lo, &hi, 0, 12288, 1024, 0x60000);
        spot.x = min.x + func_80086C84() % (max.x - min.x);
        spot.z = min.z + func_80086C84() % (max.z - min.z);
        spot.y = 0;
        lo.x = spot.x - 0x10000;
        lo.y = 0x40000;
        lo.z = spot.z - 0x10000;
        hi.x = spot.x + 0x10000;
        hi.y = 0x60000;
        hi.z = spot.z + 0x10000;
        func_8006C334(0, 3, &lo, &hi, 0, 12288, 1024, 0x60000);
        spot.x = min.x + func_80086C84() % (max.x - min.x);
        spot.z = min.z + func_80086C84() % (max.z - min.z);
        spot.y = 0;
        lo.x = spot.x - 0x10000;
        lo.y = 0x40000;
        lo.z = spot.z - 0x10000;
        hi.x = spot.x + 0x10000;
        hi.y = 0x60000;
        hi.z = spot.z + 0x10000;
        func_8006C334(0, 3, &lo, &hi, 0, 12288, 1024, 0x60000);
        max.y = 0x80000;
        min.y = 0x80000;
        min.x -= 0x10000;
        min.z -= 0x10000;
        max.x += 0x10000;
        max.z += 0x10000;
        func_80070D5C(&min, &max, 6144, 0xA5000);
        }
        }
        func_8002EA70(obj);
        break;
    case 1:
        obj->state = 2;
        break;
    case 2:
        obj->state = 3;
        break;
    case 3:
        if (obj->cell == 0xFFFF) {
            break;
        }
        func_80053790(2, obj->x, obj->z);
        obj->link->value = obj->value;
        func_80035948(obj->model, &obj->x, obj->heading, 0, 0, 0, 0, 0);
        obj->state = 4;
        obj->timer = 0;
        height = (short)(D_800C62B0[obj->cell].height + D_800C62B0[obj->cell].base);
        D_800C62B0[obj->cell].height = obj->rubble;
        func_8002E97C(obj);
        {
            Point centre;
            Vector p;

            centre.x = obj->x;
            centre.z = obj->z;
            func_80016FF4(&D_800C62B0[obj->cell], corners);
            for (i = 0; i < 4; i++) {
                p.x = fixed_mul(3276, corners[i].x - centre.x) + centre.x;
                p.z = fixed_mul(3276, corners[i].z - centre.z) + centre.z;
                p.y = func_80086C84() % fixed_mul(819, height) + fixed_mul(2457, height);
                func_8006FDB0(4, &p, 0, 0);
            }
        }
        if (obj->team == 1) {
            func_80054A30(28);
            func_8006FDB0(11, &obj->x, 0, func_80023B8C(&obj->x, 127, 100, 97, 0, 4000));
        }
        break;
    case 4:
        if (++obj->timer >= 16) {
            func_8002EA70(obj);
        }
        break;
    }
    {
        int team = obj->team;
        if (team == 1 || (team == 2 && D_800D2FE8 == 12)) {
            func_80061CC0((short)to_int(obj->x), (short)to_int(obj->z), 0, 4, 29);
        }
    }
    if (obj->state == 5) {
        *out = 1;
    }
}

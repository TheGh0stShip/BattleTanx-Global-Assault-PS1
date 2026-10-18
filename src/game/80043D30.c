typedef struct {
    char data[0x114];
} RuntimeObject;
typedef struct {
    int type;
    char pad4[4];
    int source;
    int object;
    int x;
    int y;
    int z;
} Event;
typedef struct {
    char pad0[8];
    int x;
    int y;
    int z;
    char pad14[0x208 - 0x14];
    void *owner;
    char pad20C[0x218 - 0x20C];
    int status;
    char pad21C[4];
    int push_x;
    int push_y;
    int push_z;
} Tank;
extern RuntimeObject D_800E3E68[];
extern int func_8008AE30(int, int);
extern unsigned int func_80086C84(void);
extern int func_8008ACC0(int);
extern int func_8008AD60(int);
extern void func_8003FB68(Tank *, int, RuntimeObject *, int);
extern void func_80040620(Tank *, int, int);
extern void func_80054DF8(Tank *, int);
extern int func_80022814();
extern void func_800530E0(void *, int, int);
extern void func_8003FE80(Tank *, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_80043D30(Tank *tank, Event *event) {
    unsigned int angle;
    int force;

    switch (event->type) {
    case 11:
        angle = (func_8008AE30(tank->x - event->x, tank->z - event->z) & 0xFFF) << 4;
        force = fixed_mul((((func_80086C84() >> 16) * 3277) >> 16) + 1638, 2048);
        tank->push_x += fixed_mul(func_8008ACC0(angle >> 4), force);
        tank->push_z -= fixed_mul(func_8008AD60(angle >> 4), force);
        func_8003FB68(tank, event->source, event->object == 127 ? 0 : &D_800E3E68[event->object], 0);
        break;
    case 6:
        func_80040620(tank, event->source, 1);
        func_80054DF8(tank, 34);
        if (func_80022814() != 0) {
            func_800530E0(tank->owner, 25, 0);
        }
        break;
    case 9:
    case 10:
        func_8003FE80(tank, 2048);
        break;
    case 8:
        if (!(tank->status & 0x400)) {
            func_8003FE80(tank, 1024);
        }
        tank->status |= 0x200;
        break;
    }
}

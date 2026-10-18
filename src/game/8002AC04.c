typedef struct { int x, y, z; } Vector;
typedef struct { char pad[60]; int value; } Target;
typedef struct {
    short pad;
    short pad1;
    short pad2;
    unsigned short sound;
    Target *target;
    int pad3[3];
    int effect;
    int pad4[2];
    Vector pos;
    short pad5;
    unsigned short angle;
    short active;
    unsigned char pad6;
    unsigned char state;
} Barrel;
typedef struct { unsigned char valid; char pad[3]; int x; int z; } Query;
typedef struct { int x; int z; } Hit2;
typedef struct { int x; int y; int z; } Hit3;
int func_8008AE30(int, int);
void func_80053790(int, int, int);
void func_8001B094(int);
void func_8002AAD4(Barrel *, int, int *, Query *);

static inline void burst(Barrel *b, int angle) {
    if (b->state == 2) {
        return;
    }
    func_80053790(50, b->pos.x, b->pos.z);
    b->state = 2;
    b->angle = angle;
    b->active = 1;
    b->target->value = 0;
    func_8001B094(b->sound);
}

void func_8002AC04(Barrel *b, int msg, unsigned int event, int *data, Query *q) {
    switch (event) {
    case 0:
        func_8002AAD4(b, msg, data, q);
        break;
    case 5:
        if (*data == 0 && b->state != 2) {
            q->valid = 1;
            q->x = b->pos.x;
            q->z = b->pos.z;
        }
        break;
    case 6:
        if (b->state != 2) {
            burst(b, (func_8008AE30(b->pos.x - ((Hit2 *)data)->x, b->pos.z - ((Hit2 *)data)->z) & 0xFFF) << 4);
        }
        break;
    case 3:
        if (b->state != 2) {
            burst(b, (func_8008AE30(b->pos.x - ((Hit3 *)data)->x, b->pos.z - ((Hit3 *)data)->z) & 0xFFF) << 4);
        }
        break;
    }
}

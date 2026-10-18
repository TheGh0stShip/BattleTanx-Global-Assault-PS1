typedef struct { int x, y, z; } Vector;
typedef struct { char pad[60]; int value; } Target;
typedef struct { int pad[2]; int x; int pad2; int z; } Source;
typedef struct { int pad; short type; short pad2; Source *source; } Msg;
typedef struct { int x; int pad; int z; unsigned short angle; } Hit;
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
int func_8008AE30(int, int);
void func_8006FDB0(int, Vector *, int, int);
void func_80053790(int, int, int);
void func_8001B094(int);

static inline void explode(Barrel *b, int angle) {
    if (b->state == 2) {
        return;
    }
    if (b->state == 0 && b->effect != 0) {
        func_8006FDB0(13, &b->pos, 0, 0);
    }
    func_80053790(50, b->pos.x, b->pos.z);
    b->state = 2;
    b->angle = angle;
    b->active = 1;
    b->target->value = 0;
    func_8001B094(b->sound);
}

void func_8002AAD4(Barrel *b, Msg *msg, Hit *hit, int *result) {
    switch (msg->type) {
    case 4:
        if (b->state != 2) {
            Source *src = msg->source;

            *result = 10;
            explode(b, (func_8008AE30(hit->x - src->x, hit->z - src->z) & 0xFFF) << 4);
        }
        break;
    case 12:
        if (b->state != 2) {
            *result = 1;
            explode(b, hit->angle);
        }
        break;
    }
}

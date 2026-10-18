typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad0[8];
    Vector pos;
    char pad14[4];
    int kind;
    unsigned int state;
    char pad20[4];
    int start;
    int param;
    unsigned short sound;
} Effect;

typedef struct {
    char pad0[0x9C];
    int zone;
} Tank;

typedef struct {
    short pad0[2];
    short type;
    short pad6;
    Tank *tank;
} Message;

typedef struct {
    union {
        int result;
        unsigned char valid;
    } u;
    int x;
    int z;
    int param;
    Vector pos;
} Reply;

extern int D_800D2FE0;
extern void func_8001B094(int);
extern void func_80053790(int, int, int);
extern void func_8006FDB0(int, Vector *, int, int);

static inline void detonate(Effect *e) {
    func_8001B094(e->sound);
    e->state = 2;
    e->start = D_800D2FE0;
    func_80053790(11, e->pos.x, e->pos.z);
    func_8006FDB0(4, &e->pos, 0, 0);
}

void func_800280CC(Effect *e, Message *msg, unsigned int cmd, int *busy, Reply *reply) {
    switch (cmd) {
    case 0:
        if (msg->type == 4) {
            Tank *tank = msg->tank;

            if (e->state == 0 || tank->zone == 4) {
                reply->u.result = 2;
                break;
            }
            if (e->state == 1 && e->kind == 0) {
                detonate(e);
            }
            if (e->kind == 0) {
                reply->u.result = 12;
                reply->z = 1228;
                reply->param = e->param;
                reply->pos = e->pos;
            }
        }
        break;
    case 5:
        if (*busy == 0 && e->state == 1) {
            reply->u.valid = 1;
            reply->x = e->pos.x;
            reply->z = e->pos.z;
        }
        break;
    case 6:
        if (e->state == 1) {
            e->state = 5;
        }
        break;
    case 3:
        if (e->state == 1 && e->kind == 0) {
            detonate(e);
        }
        break;
    }
}

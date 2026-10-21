typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    int m[8];
} Matrix;
typedef struct {
    char pad0[0xC];
    int team;
    char pad10[0x114 - 0x10];
} RuntimeObject;
typedef struct {
    int x;
    int z;
    int power;
    int object;
    int kind;
    int source;
} Message;
typedef struct {
    unsigned char hit;
    char pad1[3];
    int x;
    int z;
} PosReply;
typedef struct {
    Vector position;
    Vector velocity;
} StateReply;
typedef struct {
    char pad0[0xC];
    int team;
} Owner;
typedef struct {
    char pad0[0x60];
    unsigned char a;
    unsigned char b;
} View;
typedef struct {
    char pad0[8];
    Vector position;
    char pad14[0x20 - 0x14];
    Vector velocity;
    char pad2C[0x94 - 0x2C];
    void *reference;
    char pad98[0x9C - 0x98];
    int type;
    char padA0[0x17C - 0xA0];
    int state;
    int flags;
    char pad184[0x208 - 0x184];
    Owner *owner;
    char pad20C[0x218 - 0x20C];
    int status;
    char pad21C[0x2B8 - 0x21C];
    unsigned short emitter;
    char pad2BA[2];
    Matrix matrix;
} Tank;
typedef struct {
    char pad0[8];
    Tank *tank;
} Entity;
extern RuntimeObject D_800E3E68[];
extern View *D_800D3024;
extern void func_80046DD8(Tank *, void *, void *, void *);
extern void func_80053E14(Tank *);
extern void func_8003FB68(Tank *, int, RuntimeObject *, int);
extern int func_8004784C(int, int, int, int, int *);
extern void func_8004707C(Tank *, RuntimeObject *);
extern void func_800505D8(Tank *, int, int, int);
extern int func_80024114(int, int);

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline RuntimeObject *runtime_object(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline void handle_capture(Tank *tank, Message *data, PosReply *reply) {
    RuntimeObject *ro;
    int dx;
    int dz;
    int dist;
    int power;
    int result;
    int state;

    dx = fixed_to_int(tank->position.x - data->x);
    dz = fixed_to_int(tank->position.z - data->z);
    dist = dx * dx + dz * dz;
    power = data->power;
    ro = runtime_object(data->object);
    result = 0;
    if (ro->team != tank->owner->team) {
        if (tank->status & 2) {
            goto done;
        }
        if (func_8004784C(D_800D3024->a, D_800D3024->b, dist, power, &result) != 0 && tank->reference == 0) {
            func_8004707C(tank, ro);
            goto done;
        }
        state = result;
        if (tank->type == 11) {
            tank->flags |= 0x10;
        } else {
            power = 6;
            if (tank->reference != 0) {
                power = tank->state;
            }
            tank->state = 27;
            func_800505D8(tank, state, 0, power);
        }
    }
done:
    reply->hit = 1;
    reply = 0;
}

static inline void handle_hit(Tank *tank, Message *data) {
    func_8003FB68(tank, data->object, runtime_object(data->source), 0);
    data = 0;
}

static inline void handle_blast(Tank *tank, Message *data, PosReply *reply) {
    int power;

    if (data->kind == 1) {
        handle_capture(tank, data, reply);
    } else if (tank->emitter != 0xFFFF) {
        power = func_80024114(data->source, data->power);
        if (power > 0) {
            func_8003FB68(tank, power, runtime_object(data->object), 0);
        }
    }
    data = 0;
}

void func_80047258(Entity *entity, void *other, unsigned int msg, Message *data, void *out) {
    Tank *tank = entity->tank;

    if (tank == 0 || !(tank->status & 1)) {
        return;
    }
    switch (msg) {
    case 0:
        func_80046DD8(tank, other, data, out);
        break;
    case 5:
        ((PosReply *)out)->hit = 1;
        ((PosReply *)out)->x = tank->position.x;
        ((PosReply *)out)->z = tank->position.z;
        break;
    case 6:
        handle_blast(tank, data, out);
        break;
    case 3:
        handle_hit(tank, data);
        break;
    case 7:
        ((StateReply *)out)->position = tank->position;
        ((StateReply *)out)->velocity = tank->velocity;
        break;
    case 1:
        *(Matrix *)out = tank->matrix;
        break;
    case 2:
        func_80053E14(entity->tank);
        break;
    }
}

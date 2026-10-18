typedef struct {
    char pad0[0xC];
    int team;
} Owner;

typedef struct {
    char pad0[0xA0];
    unsigned int kind;
    char padA4[0x208 - 0xA4];
    Owner *owner;
} Tank;

typedef struct {
    short pad0[2];
    short type;
    short pad6;
    Tank *tank;
} Message;

typedef struct {
    char pad0[0x18];
    int value;
    char pad1C[8];
    int team;
    char pad28[3];
    unsigned char taken;
} Pickup;

typedef struct {
    int result;
    int pad4;
    int value;
} Reply;

void func_8002A1E8(Pickup *self, Message *msg, int skip, int unused, Reply *reply) {
    Tank *tank;

    if (skip != 0) {
        return;
    }
    if (self->taken == 0 && msg->type == 4) {
        tank = msg->tank;
        switch (tank->kind) {
        case 1:
            reply->result = 2;
            return;
        case 0:
        case 2:
            if (tank->owner->team != self->team) {
                reply->result = 6;
                reply->value = self->value;
                self->taken = 1;
                return;
            }
        }
    }
    reply->result = 2;
}

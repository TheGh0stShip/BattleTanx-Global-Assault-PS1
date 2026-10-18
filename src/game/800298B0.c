typedef struct {
    char pad0[0x114];
} Waypoint;

typedef struct {
    char pad0[6];
    unsigned char flags;
    char pad7;
    int x;
    int y;
    int z;
    unsigned short angle;
    char pad16[0x1C - 0x16];
    unsigned char armed;
    char pad1D[0x38 - 0x1D];
    int health;
} Object;

typedef struct {
    short pad0[2];
    short type;
} Message;

typedef struct {
    char pad0[0xC];
    int splash;
    int damage;
    int source;
    int has_source;
} Hit;

typedef struct {
    union {
        int result;
        unsigned char valid;
    } u;
    int x;
    int z;
} Reply;

extern Waypoint D_800E3E68[];
extern unsigned char D_800D2FEC;
extern int D_800D2F50;
extern void func_80029308(Object *, int, int);
extern void func_8002952C(Object *, Message *, Hit *, Reply *);
extern void func_80035948(int, int *, int, int, int, int, int, int);

void func_800298B0(Object *self_arg, Message *msg, unsigned int cmd, Hit *hit, Reply *reply) {
    Waypoint *w;
    Object *self = self_arg;

    if (self->flags & 2) {
        return;
    }
    switch (cmd) {
    case 0:
        switch (msg->type) {
        case 7:
        case 12:
        case 39:
        case 40:
        case 52:
            reply->u.result = 1;
            func_80029308(self, hit->damage, hit->has_source ? hit->source : 0);
            if (self->health <= 0) {
                func_80035948(D_800D2F50, &self->x, self->angle, 0, 0, 0, 0, 0);
                self->flags |= 2;
            }
            break;
        case 4:
        case 30:
            reply->u.result = 1;
            break;
        }
        break;
    case 5:
        reply->u.valid = 1;
        reply->x = self->x;
        reply->z = self->z;
        break;
    case 6:
        func_8002952C(self, msg, hit, reply);
        break;
    case 3:
        if (self->armed != 0) {
            if (hit->source < D_800D2FEC && hit->source != 127) {
                w = &D_800E3E68[hit->source];
            } else {
                w = 0;
            }
            func_80029308(self, hit->splash, (int)w);
            if (self->health <= 0) {
                func_80035948(D_800D2F50, &self->x, self->angle, 0, 0, 0, 0, 0);
                self->flags |= 2;
            }
        }
        break;
    }
}

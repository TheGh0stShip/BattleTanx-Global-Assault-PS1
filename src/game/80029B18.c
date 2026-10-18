typedef struct {
    char pad0[6];
    unsigned char flags;
    char pad7;
    int pos[3];
    unsigned short angle;
    char pad16[0x38 - 0x16];
    int health;
} Object;

typedef struct {
    short pad0[2];
    short type;
} Message;

typedef struct {
    char pad0[0x10];
    int damage;
    int source;
    int has_source;
} Hit;

extern int D_800D2F50;
extern void func_80029308(Object *, int, int);
extern void func_80035948(int, int *, int, int, int, int, int, int);

void func_80029B18(Object *self, Message *msg, Hit *hit, int *reply) {
    switch (msg->type) {
    case 7:
    case 12:
    case 39:
    case 40:
    case 52:
        *reply = 1;
        func_80029308(self, hit->damage, hit->has_source ? hit->source : 0);
        if (self->health <= 0) {
            func_80035948(D_800D2F50, self->pos, self->angle, 0, 0, 0, 0, 0);
            self->flags |= 2;
        }
        break;
    case 4:
    case 30:
        *reply = 1;
        break;
    }
}

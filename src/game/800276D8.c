typedef struct {
    char pad0[0x114];
} Waypoint;

typedef struct Node {
    char pad0[0x18];
    unsigned char owner;
    char pad19[0x40 - 0x19];
} Node;

typedef struct {
    char pad0[0x16];
    signed char health;
    unsigned char state;
    char pad18[0x3A - 0x18];
    short link;
} Crate;

typedef struct {
    short pad0[2];
    short type;
    short pad6;
    void *sender;
} Message;

typedef struct {
    char pad0[0x10];
    int damage;
} Hit;

extern Waypoint D_800E3E68[];
extern Node *D_800D3258;
extern void func_800531D4(Waypoint *, int);
extern void func_80033F64(void *, Node *);

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_800276D8(Crate *self, Message *msg, Hit *hit, int *reply) {
    int health;
    int link;

    switch (msg->type) {
    case 7:
    case 12:
    case 39:
    case 52:
        health = self->health - hit->damage;
        if (health <= 0) {
            self->health = 0;
        } else {
            self->health = health;
        }
        link = self->link;
        if (link != -1) {
            func_800531D4(waypoint_get(((Node *)((char *)D_800D3258 + (link << 6)))->owner), 9);
        }
        *reply = 1;
        break;
    case 40:
        *reply = 5;
        break;
    case 4:
        if (self->link != -1) {
            func_80033F64(msg->sender, &D_800D3258[self->link]);
        }
        if (self->state == 7) {
            break;
        }
    case 75:
        *reply = 1;
        break;
    }
}

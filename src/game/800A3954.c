typedef struct Unit {
    unsigned char pad0[0x46];
    unsigned char state;
    unsigned char pad47[0xF0 - 0x47];
} Unit;

typedef struct Group {
    unsigned char pad0[0x0C];
    Unit *units;
} Group;

typedef struct Node {
    unsigned char pad0[0x0C];
    int multi;
    Group *group;
    unsigned char pad14[0x46 - 0x14];
    unsigned char state;
    unsigned char pad47[0xE6 - 0x47];
    unsigned short active;
} Node;

int func_800A3954(Node *node)
{
    int i;
    int r;
    Unit *u;

    if (node->active == 0) {
        return 1;
    }
    if (node->multi != 0) {
        if (node->state != 0xFF) {
            return 1;
        }
        u = node->group->units;
        for (i = 0; i < 4; i++, u++) {
            if (u->state != 0xFF && u->state != 0) {
                return 1;
            }
        }
        return 0;
    }
    r = 0;
    if (((Unit *)node->group)->state != 0xFF || node->state != 0xFF) {
        r = 1;
    }
    return r;
}

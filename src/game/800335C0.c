typedef struct { int pad; unsigned short count; } Counter;
typedef struct { char pad[12]; Counter *counter; char rest[0x114 - 16]; } Waypoint;
typedef struct { char pad[24]; unsigned char waypoint; } Ref;
typedef struct { short pad; short next; short type; short pad2; int pad3; int used; int pad4; Ref *ref; char rest[40]; } Node;
extern short D_800D3254;
extern Node *D_800D3258;
extern Waypoint D_800E3E68[];

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_800335C0(void) {
    short i;
    Node *n;

    i = D_800D3254;
    while (i != -1) {
        n = &D_800D3258[i];
        if (n->type == 8 && n->used == 0) {
            waypoint_at(n->ref->waypoint)->counter->count++;
        }
        i = n->next;
    }
}

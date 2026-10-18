typedef struct Node {
    unsigned short id;
    short next;
    short kind;
    char pad06[0x12 - 6];
    unsigned char owner;
    char pad13[0x40 - 0x13];
} Node;
typedef struct Waypoint {
    char pad000[0xBC];
    unsigned char count;
    char pad0BD[0x114 - 0xBD];
} Waypoint;
extern Waypoint D_800E3E68[];
extern Node *D_800D3258;
extern short D_800D3254;
typedef struct {
    char pad0[8];
    unsigned char count;
} Game;
extern Game D_800D2FE4;

static inline Waypoint *waypoint(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80053268(void) {
    short index;
    Node *node;

    for (index = D_800D3254; index != -1; index = node->next) {
        node = (&D_800D3258[index]);
        if (node->kind == 14 && node->owner >= D_800D2FE4.count) {
            waypoint(node->owner)->count++;
        }
    }
}

typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Node {
    unsigned short id;
    unsigned short found;
    short kind;
    short next;
} Node;
typedef struct ProbeHit {
    Node *node;
    char pad04[0x24 - 4];
} ProbeHit;
typedef struct NodeClass {
    void (*update)();
    void (*notify)(Node *, int, int, void *, int);
    void (*draw)();
} NodeClass;
typedef struct BlastInfo {
    Vector pos;
    int damage;
    int unk10;
    int owner;
} BlastInfo;
extern int D_800A4394;
extern short D_800C628C;
extern NodeClass D_800D32F4[];
unsigned short func_8001AED4(int, short, short, short, short, short, short, short, short, short, int, int);
unsigned short func_80017AAC(unsigned short, int, ProbeHit *, int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_800235E0(Vector *pos, int radius, int damage, int owner, int arg4) {
    ProbeHit hits[8];
    BlastInfo info;
    unsigned short count;
    int i;
    unsigned short id;
    int found;

    int r = radius;

    if (D_800A4394 == 1) {
        return;
    }
    D_800A4394 = 1;
    id = func_8001AED4(0, to_int(pos->x) >> 2, to_int(pos->z) >> 2, to_int(pos->y) >> 2,
                       -r, r, -r, r, -r, r, 0, 0);
    D_800C628C = 0;
    found = func_80017AAC(id, arg4, hits, 0, 0);
    count = found;
    if (found != 0) {
        info.pos = *pos;
        info.damage = damage;
        info.owner = owner;
        i = 0;
        if (i < found) {
            do {
                Node *node = hits[i].node;
                if (node != 0 && D_800D32F4[node->kind].notify != 0 && node->kind != -1) {
                    D_800D32F4[node->kind].notify(hits[i].node, 1, 3, &info, 0);
                }
            } while (++i < count);
        }
    }
    D_800A4394 = 0;
}

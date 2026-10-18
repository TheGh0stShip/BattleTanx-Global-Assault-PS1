typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Node {
    short id;
    short next;
    short kind;
    char pad06[0x40 - 6];
} Node;
typedef struct QueryResult {
    unsigned char type;
    char pad01[3];
    int x;
    int z;
} QueryResult;
typedef struct QueryInfo {
    int param;
} QueryInfo;
typedef struct NodeClass {
    void (*update)();
    void (*query)(Node *, int, int, QueryInfo *, QueryResult *);
    void (*draw)();
} NodeClass;
typedef struct SortEntry {
    Node *node;
    int id;
    int dist;
} SortEntry;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
extern Node *D_800D3258;
extern short D_800D3260[];
extern NodeClass D_800D32F4[];
extern int D_800D366C;
extern SortEntry D_800D3670[];
extern int D_800D5A70;
extern int D_800D5A74;
extern int D_800D5A78;
extern int D_800D5A7C;
extern int D_800D5A80;
extern int D_800D5A84;
extern unsigned char D_800D5A88;
extern Pos2 D_800D5A8C;
void func_800238C4(SortEntry *, int);

static inline int imul(int a, int b) {
    return a * b;
}

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void copy_pos(Pos2 *dst, Vector *src) {
    dst->x = src->x;
    dst->z = src->z;
}

int func_80023B8C(Vector *pos, int arg1, int arg2, unsigned char priority, int param, int radius) {
    QueryResult result;
    QueryInfo info;
    int kind;
    int index;
    Node *node;
    SortEntry *entry;
    int dx;
    int dz;

    if (D_800D5A88 >= priority) {
        return 0;
    }
    D_800D5A74 = 0;
    D_800D5A84 = arg2;
    D_800D5A78 = arg1;
    D_800D366C = 0;
    copy_pos(&D_800D5A8C, pos);
    D_800D5A7C = param;
    D_800D5A88 = priority;
    info.param = param;
    for (kind = 0; kind < 74; kind++) {
        if (D_800D32F4[kind].query == 0) {
            continue;
        }
        index = D_800D3260[kind];
        while (index != -1) {
            node = &D_800D3258[index];
            result.type = 0;
            if (D_800D32F4[node->kind].query != 0 && node->kind != -1) {
                D_800D32F4[node->kind].query(node, 0, 5, &info, &result);
            }
            if (result.type != 0 && D_800D366C != 768) {
                entry = &D_800D3670[D_800D366C];
                entry->node = node;
                entry->id = node->id;
                if (result.type == 2) {
                    entry->dist = -1;
                } else {
                    dx = to_int(D_800D5A8C.x - result.x);
                    dz = to_int(D_800D5A8C.z - result.z);
                    D_800D3670[D_800D366C].dist = dx * dx + dz * dz;
                }
                D_800D366C++;
            }
            index = node->next;
        }
    }
    func_800238C4(D_800D3670, D_800D366C);
    for (D_800D5A70 = 0; D_800D5A70 < D_800D366C; D_800D5A70++) {
        if (D_800D3670[D_800D5A70].dist != -1) {
            break;
        }
    }
    D_800D5A80 = imul(radius, radius);
    return 1;
}

typedef struct Node {
    unsigned short id;
    short next;
    short kind;
    unsigned short ref;
} Node;

typedef struct NodeClass {
    void (*update)();
    void (*touch)();
    void (*draw)();
} NodeClass;

typedef struct {
    Node *node;
    char pad04[0x24 - 4];
} ProbeHit;

extern short D_800C628C;
extern NodeClass D_800D32F4[];
unsigned short func_80017AAC(unsigned short, int, ProbeHit *, int, int);

static inline int probe_hits(unsigned short id, ProbeHit *hits) {
    D_800C628C = 0;
    return func_80017AAC(id, 0x100000, hits, 2, 0);
}

void func_800265CC(Node *self) {
    ProbeHit hits[8];
    int count;
    int i;

    count = probe_hits(self->ref, hits);
    for (i = 0; i < count; i++) {
        Node *node = hits[i].node;

        if (node != 0) {
            NodeClass *cls = &D_800D32F4[node->kind];

            if (cls->touch != 0 && node->kind != -1) {
                cls->touch(hits[i].node, self, 0, 0, 0);
            }
        }
    }
}

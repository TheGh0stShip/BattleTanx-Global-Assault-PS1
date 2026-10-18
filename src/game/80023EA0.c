typedef struct Node {
    short id;
    short next;
    short kind;
} Node;

typedef struct NodeClass {
    void (*update)();
    void (*touch)();
    void (*draw)();
} NodeClass;

typedef struct {
    Node *node;
    int id;
    int dist;
} Contact;

typedef struct {
    int x;
    int z;
} Point;

typedef struct {
    Point center;
    int radius_sq;
    int a;
    int b;
    int c;
} Blast;

typedef struct {
    unsigned char hit;
    char pad1[3];
    int x;
    int z;
} Reply;

extern Point D_800D5A8C;
extern int D_800D5A78;
extern int D_800D5A7C;
extern int D_800D5A84;
extern int D_800D5A70;
extern int D_800D366C;
extern Contact D_800D3670[];
extern NodeClass D_800D32F4[];

void func_80023EA0(int radius) {
    Blast blast;
    Reply reply;
    int r2;
    int i;
    Contact *c;
    NodeClass *cls;

    blast.center.x = D_800D5A8C.x;
    blast.center.z = D_800D5A8C.z;
    r2 = radius * radius;
    blast.a = D_800D5A78;
    blast.c = D_800D5A84;
    blast.b = D_800D5A7C;
    blast.radius_sq = r2;
    for (i = 0; i < D_800D366C; i++) {
        if (D_800D3670[i].dist != -1) {
            break;
        }
        if (D_800D3670[i].node->id == D_800D3670[i].id) {
            reply.hit = 0;
            cls = &D_800D32F4[D_800D3670[i].node->kind];
            if (cls->touch != 0 && D_800D3670[i].node->kind != -1) {
                cls->touch(D_800D3670[i].node, 0, 6, &blast, &reply);
            }
            if (reply.hit) {
                D_800D3670[i].id = 1;
            }
        }
    }
    for (; D_800D5A70 < D_800D366C; D_800D5A70++) {
        c = &D_800D3670[D_800D5A70];
        if (r2 < c->dist) {
            break;
        }
        if (c->node->id == c->id) {
            reply.hit = 0;
            cls = &D_800D32F4[c->node->kind];
            if (cls->touch != 0 && c->node->kind != -1) {
                cls->touch(c->node, 0, 6, &blast, &reply);
            }
            if (reply.hit) {
                D_800D3670[D_800D5A70].id = 1;
            }
        }
    }
}

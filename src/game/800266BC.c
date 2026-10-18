typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    int x;
    int z;
} Corner;

typedef struct {
    char pad0[0x28];
} Sprite;

typedef struct Node {
    unsigned short id;
    char pad2[0x40 - 2];
} Node;

typedef struct {
    char pad0[6];
    unsigned short sprite;
    char pad08[0x3C - 8];
    short node;
    unsigned short node_id;
} Object;

extern Sprite D_800C62B0[];
extern Node *D_800D3258;
extern void func_80016FF4(Sprite *, Corner *);
extern Node *func_80070D5C(Vector *, Vector *, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_800266BC(Object *obj, int height, int arg2, int arg3) {
    Corner corners[4];
    Vector min;
    Vector max;
    Node *node;
    Corner *c = corners;
    int i;
    int d;

    func_80016FF4(&D_800C62B0[obj->sprite], c);
    min.z = 0x7FFFFFFF;
    min.x = 0x7FFFFFFF;
    max.z = 0x80000000;
    max.x = 0x80000000;
    for (i = 0; i < 4; i++) {
        if (c[i].x < min.x) {
            min.x = c[i].x;
        }
        if (c[i].x > max.x) {
            max.x = c[i].x;
        }
        if (c[i].z < min.z) {
            min.z = c[i].z;
        }
        if (c[i].z > max.z) {
            max.z = c[i].z;
        }
    }
    d = fixed_mul(327, max.x - min.x);
    min.x += d;
    max.x -= d;
    d = fixed_mul(327, max.z - min.z);
    min.z += d;
    max.z -= d;
    max.y = height;
    min.y = height;
    node = func_80070D5C(&min, &max, arg2, arg3);
    if (node != 0) {
        obj->node = node - D_800D3258;
        obj->node_id = node->id;
    }
}

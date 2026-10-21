typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    int x;
    int z;
} Point;

typedef struct {
    short id;
    char pad2[6];
    int flag;
    int x;
    char pad10[4];
    int z;
    unsigned char kind;
    char pad19[0x40 - 0x19];
} Node;

typedef struct {
    char pad0[0x14];
    unsigned short base;
    char pad16[0x20 - 0x16];
    unsigned short height;
    char pad22[0x28 - 0x22];
} Sprite;

typedef struct {
    char pad0[0xE];
    short frame;
} Anim;

typedef struct {
    char pad0[8];
    Anim *anim;
} Model;

typedef struct {
    char pad0[0x3C];
    int model;
} Instance;

typedef struct {
    char pad0[6];
    unsigned short sprite;
    Vector pos;
    unsigned short angle;
    signed char timer;
    unsigned char state;
    int model_id;
    Model *model;
    char pad20[0x2C - 0x20];
    int sound_a;
    int sound_b;
    Instance *instance;
    short counter;
    short link;
    short node;
    short node_id;
} Building;

extern Sprite D_800C62B0[];
extern Node *D_800D3258;
extern int D_800EAC1C;
extern unsigned int func_80086C84(void);
extern void func_80035948(int, Vector *, int, int, int, int, int, int);
extern void func_800265CC(Building *);
extern void func_80016FF4(Sprite *, Point *);
extern void func_8006C334(int, int, Vector *, Vector *, int, int, int, int);
extern void func_80070D5C(Vector *, Vector *, int, int);
extern void func_80053790(int, int, int);
extern void func_8006FDB0(int, Vector *, int, int);
extern void func_800266BC(Building *, int, int, int);
extern void func_80071320(Node *);
extern void func_8002688C(Building *);
extern void func_80061CC0(short, short, int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}


void func_80026988(Building *obj, int *done) {
    switch (obj->state) {
    case 0:
        if (obj->timer > 0) {
            break;
        }
        if (D_800EAC1C != 0 || (func_80086C84() & 7) != 0) {
            obj->state = 1;
            break;
        }
        {
            int i;
            int height;
            Point *c;

            {
                Point corners[4];
                Vector min;
                Vector max;
                Vector p;
                Vector lo;
                Vector hi;

                func_80035948(obj->sound_a, &obj->pos, obj->angle, 0, 0, 0, 0, 0);
                func_80035948(obj->sound_b, &obj->pos, obj->angle, 0, 0, 0, 0, 0);
                func_800265CC(obj);
                __asm__ ("");
                c = corners;
                func_80016FF4(&D_800C62B0[obj->sprite], c);
                height = (short)(D_800C62B0[obj->sprite].height + D_800C62B0[obj->sprite].base) << 14;
                min.x = min.z = 0x0C350000;
                max.x = max.z = -0x0C350000;
                for (i = 0; i < 4; i++, c++) {
                    int x = c->x;
                    int z = c->z;

                    if (x < min.x) {
                        min.x = x;
                    }
                    if (max.x < x) {
                        max.x = x;
                    }
                    if (z < min.z) {
                        min.z = z;
                    }
                    if (max.z < z) {
                        max.z = z;
                    }
                }
                min.y = 0;
                max.y = height;
                func_8006C334(0, 6, &min, &max, 0, 8192, 819, 0x19000);
                func_8006C334(0, 6, &min, &max, 0, 4096, 819, 0x19000);
                func_8006C334(0, 6, &min, &max, 0, 5461, 819, 0x19000);
                p.x = min.x + func_80086C84() % (max.x - min.x);
                p.z = min.z + func_80086C84() % (max.z - min.z);
                p.y = 0;
                lo.x = p.x - 0x10000;
                lo.y = 0x40000;
                lo.z = p.z - 0x10000;
                hi.x = p.x + 0x10000;
                hi.y = 0x60000;
                hi.z = p.z + 0x10000;
                func_8006C334(0, 3, &lo, &hi, 0, 12288, 1024, 0x60000);
                p.x = min.x + func_80086C84() % (max.x - min.x);
                p.z = min.z + func_80086C84() % (max.z - min.z);
                p.y = 0;
                lo.x = p.x - 0x10000;
                lo.y = 0x40000;
                lo.z = p.z - 0x10000;
                hi.x = p.x + 0x10000;
                hi.y = 0x60000;
                hi.z = p.z + 0x10000;
                func_8006C334(0, 3, &lo, &hi, 0, 12288, 1024, 0x60000);
                p.x = min.x + func_80086C84() % (max.x - min.x);
                p.z = min.z + func_80086C84() % (max.z - min.z);
                p.y = 0;
                lo.x = p.x - 0x10000;
                lo.y = 0x40000;
                lo.z = p.z - 0x10000;
                hi.x = p.x + 0x10000;
                hi.y = 0x60000;
                hi.z = p.z + 0x10000;
                func_8006C334(0, 3, &lo, &hi, 0, 12288, 1024, 0x60000);
                min.y = max.y = 0x80000;
                min.x -= 0x10000;
                min.z -= 0x10000;
                max.x += 0x10000;
                max.z += 0x10000;
                func_80070D5C(&min, &max, 6144, 0xA5000);
            }
        }
        func_8002688C(obj);
        break;
    case 1:
        obj->state = 2;
        break;
    case 2:
        obj->state = 3;
        break;
    case 3:
        func_80053790(2, obj->pos.x, obj->pos.z);
        obj->instance->model = obj->model_id;
        obj->state = 4;
        obj->counter = 0;
        func_80035948(obj->sound_a, &obj->pos, obj->angle, 0, 0, 0, 0, 0);
        func_800265CC(obj);
        {
            Point corners[4];
            int i;
            int height;
            Point center;
            Vector q;

            center.x = obj->pos.x;
            center.z = obj->pos.z;
            func_80016FF4(&D_800C62B0[obj->sprite], corners);
            height = (short)(D_800C62B0[obj->sprite].height + D_800C62B0[obj->sprite].base) << 14;
            D_800C62B0[obj->sprite].height = obj->model->anim->frame;
            for (i = 0; i < 4; i++) {
                q.x = fixed_mul(3276, corners[i].x - center.x) + center.x;
                q.z = fixed_mul(3276, corners[i].z - center.z) + center.z;
                q.y = func_80086C84() % fixed_mul(819, height) + fixed_mul(2457, height);
                func_8006FDB0(4, &q, 0, 0);
            }
        }
        break;
    case 4:
        if (++obj->counter == 12) {
            func_800266BC(obj, obj->model->anim->frame << 14, 8192, 0xA5000);
        }
        if (obj->counter >= 16) {
            obj->state = 5;
            obj->timer = 15;
            obj->instance->model = (int)obj->model;
        }
        break;
    case 5:
        if (obj->timer > 0) {
            break;
        }
        {
            Node *n = &D_800D3258[obj->node];

            if (n->id == obj->node_id) {
                func_80071320(n);
            }
        }
        obj->state = 6;
        obj->counter = 0;
        func_80035948(obj->sound_b, &obj->pos, obj->angle, 0, 0, 0, 0, 0);
        func_80053790(2, obj->pos.x, obj->pos.z);
        {
            Point corners[4];
            int i;
            int height;
            Point center;
            Vector q;

            center.x = obj->pos.x;
            center.z = obj->pos.z;
            func_80016FF4(&D_800C62B0[obj->sprite], corners);
            height = (short)(D_800C62B0[obj->sprite].height + D_800C62B0[obj->sprite].base) << 14;
            for (i = 0; i < 4; i++) {
                q.x = fixed_mul(3276, corners[i].x - center.x) + center.x;
                q.z = fixed_mul(3276, corners[i].z - center.z) + center.z;
                q.y = func_80086C84() % fixed_mul(819, height) + fixed_mul(2457, height);
                func_8006FDB0(4, &q, 0, 0);
            }
        }
        break;
    case 6:
        if (++obj->counter >= 16) {
            func_8002688C(obj);
        }
        break;
    }
    if (obj->link != -1) {
        Node *n = &D_800D3258[obj->link];
        int mode;

        mode = 2;
        if (n->flag) {
            mode = 0x8002;
        }
        func_80061CC0(fixed_to_int(n->x), fixed_to_int(n->z), 0, n->kind, mode);
    }
    if (obj->link == -1 && obj->state == 7) {
        *done = 1;
    }
}

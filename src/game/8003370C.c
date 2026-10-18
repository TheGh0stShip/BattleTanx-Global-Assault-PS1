typedef struct { int x, y, z; } Vector;
typedef struct Item Item;
struct Item { int pad[4]; int model; int pad2[2]; Item *next; };
int func_8008AD60(int);
int func_8008ACC0(int);
void func_8006A1BC(int, Vector *, int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_8003370C(Item *list, Vector *center, unsigned short base) {
    Item *it;
    int count;
    int i;
    int angle;
    Vector v;

    count = 0;
    for (it = list; it != 0; it = it->next) {
        count++;
    }
    if (count == 0) {
        return;
    }
    if (count == 1) {
        func_8006A1BC(list->model, center, 0, 0x8000, 0);
        return;
    }
    for (it = list, i = 0; it != 0; it = it->next, i++) {
        angle = (unsigned short)(base + 0xFFFF / count * i) >> 4;
        v.x = center->x + fixed_mul(0x3C000, func_8008AD60(angle));
        v.y = center->y;
        v.z = center->z + fixed_mul(0x3C000, func_8008ACC0(angle));
        func_8006A1BC(it->model, &v, 0, 0x8000, 0);
    }
}

typedef struct { int x, y, z; } Vector;
typedef struct {
    int pad[2];
    Vector pos;
    Vector dir;
    int length;
    int handle;
    int life;
    short kind;
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
    short pad2;
    int e;
    int f;
} Beam;
int func_80022BD4(void);
void func_8002382C(int);
Beam *func_800237D0(int, int);
int func_8008ABF0(int);
void func_8006C334(Beam *, int, int, int, int, int, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_8002E078(Vector *pos, Vector *dir, short kind, unsigned char c, unsigned char d, int e, int f) {
    int handle;
    Beam *beam;

    handle = func_80022BD4();
    if (handle == 0) {
        return;
    }
    beam = func_800237D0(40, 60);
    if (beam == 0) {
        func_8002382C(handle);
        return;
    }
    beam->pos = *pos;
    beam->dir = *dir;
    beam->kind = kind;
    beam->handle = handle;
    beam->a = 0;
    beam->b = 0;
    beam->life = 100;
    beam->c = c;
    beam->d = d;
    beam->e = e;
    beam->f = f;
    beam->length = func_8008ABF0(fixed_mul(dir->x, dir->x) + fixed_mul(dir->y, dir->y) + fixed_mul(dir->z, dir->z));
    func_8006C334(beam, 10, 0, 0, 0, 4096, 4096, 0x7FFFFFFF);
}

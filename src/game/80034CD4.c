typedef struct { int x, y, z; } Vector;
typedef struct {
    int pad[2];
    int x;
    int z;
    short a;
    unsigned char b;
    char pad1;
    short c;
    unsigned char d;
    char pad2;
    short e;
    short pad3;
    int height;
    int f;
    unsigned char g;
    unsigned char h;
    unsigned char alpha;
    unsigned char flag;
    int zero;
    int i;
    int j;
} Particle;
Particle *func_800237D0(int, int);

Particle *func_80034CD4(Vector *pos, short a, unsigned char b, short c, short e, int f, unsigned char g,
                        unsigned char h, int unused, int i, int j, unsigned char alpha) {
    Particle *p;

    p = func_800237D0(14, 52);
    if (p == 0) {
        return 0;
    }
    p->x = pos->x;
    p->z = pos->z;
    p->a = a;
    p->b = b;
    p->c = c;
    p->d = 0;
    p->e = e;
    p->height = -1000;
    p->f = f * 2;
    p->g = g;
    p->h = h;
    p->zero = 0;
    p->i = i;
    p->j = j;
    p->alpha = alpha;
    if (alpha == 0) {
        p->alpha = 255;
    }
    p->flag = 0;
    return p;
}

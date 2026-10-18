typedef struct {
    short x, y, z, pad;
} SVec;

typedef struct {
    int x, y, z;
} Vector;

typedef struct {
    short cmd;
    unsigned char arg;
    unsigned char value;
} AnimStep;

typedef struct {
    int pad0;
    int a;
    int life;
    SVec pos;
    unsigned short angle;
    short v16;
    short v18;
    short v1A;
    short v1C;
    signed char spin;
    char active;
    short rot;
    short rot_speed;
    unsigned char r, g, b;
    unsigned char anim;
    unsigned char frame;
    unsigned char timer;
} Particle;

extern AnimStep *D_800ADF48[];

static inline void particle_age(Particle *p, int dt) {
    int life;
    int elapsed;
    int timer;
    AnimStep *step;

    life = p->life;
    p->life = life - dt;
    if (p->anim != 255) {
        timer = p->timer;
        elapsed = (life >> 12) - (p->life >> 12);
        if (elapsed < timer) {
            p->timer -= elapsed;
            return;
        }
        p->frame++;
        step = (AnimStep *)((p->frame << 2) + (int)D_800ADF48[p->anim]);
        if (step->cmd == 1) {
            p->frame = step->value;
        }
        p->timer = D_800ADF48[p->anim][p->frame].value;
    }
}

void func_8006DAEC(Particle *p, Vector *drift, int dt) {
    int frac;

    p->pos.x += p->v16 * dt / 65536;
    p->pos.y += p->v18 * dt / 65536;
    p->pos.z += p->v1A * dt / 65536;
    frac = (p->life << 12) / p->a;
    p->r = frac / 64;
    p->g = frac / 128;
    p->b = frac / 32;
    p->rot += p->rot_speed * dt / 4096;
    particle_age(p, dt);
}

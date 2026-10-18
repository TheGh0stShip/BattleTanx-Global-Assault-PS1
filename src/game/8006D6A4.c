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
    unsigned short rot;
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

void func_8006D6A4(Particle *p, Vector *drift, int dt) {
    int shade;

    p->pos.x -= drift->x >> 12;
    p->pos.y -= drift->y >> 12;
    p->pos.z -= drift->z >> 12;
    if (p->life < 0x14000) {
        shade = p->life / 20;
    } else {
        shade = 4096 - (p->life - 0x14000) / 10;
    }
    p->r = shade / 32;
    p->g = shade / 32;
    p->b = shade / 32;
    particle_age(p, dt);
}

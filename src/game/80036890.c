typedef struct { int x, y, z; } Vector;
typedef struct { short id; short next; short kind; } Node;
typedef struct {
    char pad00[8];
    Vector pos;
    Vector vel;
    int dist;
    unsigned char owner;
    char pad25[3];
    int life;
    int source;
} Shot;
typedef struct { Node *node; int pad; Vector pos; char pad14[0x28 - 0x14]; } Hit;
typedef struct {
    Vector pos;
    unsigned short heading;
    short pad;
    int source;
    void *waypoint;
    int team;
    char pad1C[0x28 - 0x1C];
} Impact;
typedef struct { unsigned int kind; unsigned short heading; char pad[0x1C - 6]; } Reply;
typedef struct {
    void (*update)();
    void (*query)(Node *, Shot *, int, Impact *, Reply *);
    void (*draw)();
} NodeClass;
typedef struct { char pad[0x114]; } Waypoint;

extern Shot *func_800237D0(int, int);
extern unsigned short func_80019D80(Vector *, Vector *, int, int, int, Hit *);
extern int func_8008AE30(int, int);
extern int func_8008AD60(int);
extern int func_8008ACC0(int);
extern short D_800C628C;
extern Reply D_800BE5E8;
extern Waypoint D_800E3E68[];
extern NodeClass D_800D32F4[];

int func_80036890(Vector *pos, Vector *vel, unsigned short heading, unsigned char wp, int source, int ignore,
                  unsigned char team, int depth);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void gte_ldlzc(int value) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(value));
}

static inline void gte_stlzc(int *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

static inline int leading_zeros(int value) {
    int count;

    gte_ldlzc(value);
    gte_stlzc(&count);
    return count;
}

int abs(int);

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int sign;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    sign = numerator & 0x80000000;
    negative = sign ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        n <<= n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)n / (d >> scale);
            } else {
                quotient = (unsigned int)n / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)n / (d >> -excess);
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int length3(int dx, int dy, int dz) {
    int a1;
    int a2;
    int r;

    a1 = func_8008AE30(dy, dz) & 0xFFF;
    r = fixed_mul(func_8008AD60(a1), dy) + fixed_mul(func_8008ACC0(a1), dz);
    a2 = func_8008AE30(dx, r) & 0xFFF;
    return fixed_mul(func_8008AD60(a2), dx) + fixed_mul(func_8008ACC0(a2), r);
}

int func_80036890(Vector *pos, Vector *vel, unsigned short heading, unsigned char wp, int source, int ignore,
                  unsigned char team, int depth)
{
    Vector target;
    Hit hit;
    Impact impact;
    Reply reply;
    Vector next;
    Vector dir;
    Shot *shot;
    int done;
    int hitting;
    int den;
    int scale;
    int angle;
    unsigned char index;
    short kind;

    done = 0;
    index = wp;
    shot = func_800237D0(52, 48);
    if (shot == 0 || depth <= 0) {
        return -1;
    }
    shot->vel.x = -vel->x;
    shot->vel.y = -vel->y;
    shot->vel.z = -vel->z;
    shot->owner = wp;
    shot->life = 8;
    shot->source = source;
    target.y = pos->y + vel->y * 125 * 0x80000;
    if (target.y < 0) {
        den = pos->y - target.y;
        if (den == 0) {
            den = 2;
        }
        scale = fixed_mul(0x3E80000, fixed_div(pos->y, den));
        target.x = pos->x + fixed_mul(vel->x, scale);
        target.z = pos->z + fixed_mul(vel->z, scale);
        target.y = 0;
    } else {
        target.x = pos->x + fixed_mul(0x3E80000, vel->x);
        target.z = pos->z + fixed_mul(0x3E80000, vel->z);
    }
    do {
        D_800C628C = 1;
        hitting = func_80019D80(pos, &target, 0x64940B, 0, ignore, &hit);
        if (hitting != 0 && hit.node != 0 && (int)hit.node != ignore) {
            reply = D_800BE5E8;
            impact.pos.x = hit.pos.x;
            impact.pos.y = hit.pos.y;
            impact.pos.z = hit.pos.z;
            impact.heading = heading;
            if (index != 127) {
                impact.waypoint = &D_800E3E68[index];
            } else {
                impact.waypoint = 0;
            }
            impact.source = source;
            impact.team = team;
            kind = hit.node->kind;
            if (D_800D32F4[kind].query != 0 && kind != -1) {
                D_800D32F4[kind].query(hit.node, shot, 0, &impact, &reply);
            }
            switch (reply.kind) {
            case 1:
                done = 1;
                break;
            case 2:
                pos->x = hit.pos.x + vel->x;
                pos->y = hit.pos.y + vel->y;
                hitting = 0;
                pos->z = hit.pos.z + vel->z;
                if (length3(pos->x - target.x, pos->y - target.y, pos->z - target.z) < 0xA000) {
                    do {
                        done = 1;
                    } while (0);
                }
                break;
            case 5:
                angle = reply.heading >> 4;
                hitting = 0;
                dir.x = func_8008AD60(angle);
                dir.y = vel->y;
                dir.z = func_8008ACC0(reply.heading >> 4);
                next.x = hit.pos.x + dir.x;
                next.y = hit.pos.y + dir.y;
                next.z = hit.pos.z + dir.z;
                func_80036890(&next, &dir, reply.heading, 127, source, (int)hit.node, team, depth - 1);
                target.x = hit.pos.x;
                target.y = hit.pos.y;
                done = 1;
                target.z = hit.pos.z;
                break;
            }
        } else {
            do {
                done = 1;
            } while (0);
        }
    } while (!done);
    if (hitting != 0) {
        target.x = hit.pos.x;
        target.y = hit.pos.y;
        target.z = hit.pos.z;
    }
    shot->dist = length3(target.x - pos->x, target.y - pos->y, target.z - pos->z);
    shot->pos.x = target.x;
    shot->pos.y = target.y;
    shot->pos.z = target.z;
    return 0;
}

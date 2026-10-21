typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct Obj {
    int pad0;
    short kind;
} Obj;

typedef struct Hit {
    Obj *obj;
    int pad04;
    Vec pos;
    int pad14[4];
} Hit;

typedef struct Impact {
    Vec pos;
    short flag;
    short pad0E;
    int damage;
    void *owner;
    int count;
    int pad1C;
    int extra;
} Impact;

typedef struct Response {
    int code;
    int data[6];
} Response;

typedef struct ObjClass {
    void *update;
    void (*hit)(Obj *, void *, int, Impact *, Response *);
    void *draw;
} ObjClass;

typedef struct Shell {
    int pad0[2];
    Vec pos;
    Vec vel;
    int timer;
    unsigned short damage;
    unsigned short owner;
    unsigned short landed;
    unsigned short spin;
    Obj *ignore;
} Shell;

typedef struct Waypoint {
    char data[0x114];
} Waypoint;

extern int D_800DE30C;
extern short D_800C628C;
extern Response D_800C05E8;
extern ObjClass D_800D32F4[];
extern Waypoint D_800E3E68[];
extern unsigned short func_80019D80(Vec *, Vec *, int, int, int, Hit *);
extern void func_80070D5C(Vec *, Vec *, int, int);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline Waypoint *waypoint_ptr(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80072F54(Shell *shell, int *done) {
    Hit hit;
    Vec next;
    int dt;
    int stop = 0;

    if (shell->timer <= 0) {
        *done = 1;
        return;
    }
    dt = D_800DE30C;
    shell->timer -= dt;
    shell->spin += fixed_mul(dt, 122);
    if (shell->landed) {
        return;
    }
    next.x = shell->pos.x + fixed_mul(dt, shell->vel.x);
    next.y = shell->pos.y + fixed_mul(dt, shell->vel.y);
    next.z = shell->pos.z + fixed_mul(dt, shell->vel.z);
    shell->vel.y -= fixed_mul(dt, 8192);
    D_800C628C = 1;
    if (func_80019D80(&shell->pos, &next, 0x64940B, 0, 0, &hit)) {
        if (shell->ignore == 0 || hit.obj != shell->ignore) {
            if (hit.obj == 0) {
                stop = 1;
            } else {
                Impact impact;
                Response response;

                response = D_800C05E8;
                impact.pos.x = hit.pos.x;
                impact.pos.y = hit.pos.y;
                impact.pos.z = hit.pos.z;
                impact.flag = 0;
                impact.damage = shell->damage;
                impact.owner = waypoint_ptr(shell->owner);
                impact.count = 1;
                impact.extra = 0;
                if (D_800D32F4[hit.obj->kind].hit != 0 && hit.obj->kind != -1) {
                    D_800D32F4[hit.obj->kind].hit(hit.obj, shell, 0, &impact, &response);
                }
                switch ((unsigned int)response.code) {
                case 1:
                case 3:
                case 5:
                    stop = 1;
                    break;
                }
            }
            shell->ignore = 0;
        }
    }
    if (stop) {
        shell->landed = 1;
        return;
    }
    if (next.y <= 0) {
        Vec lo;
        Vec hi;

        shell->landed = 1;
        lo.x = shell->pos.x - 0x100000;
        lo.y = shell->pos.y + 0x40000;
        lo.z = shell->pos.z - 0x100000;
        hi.x = shell->pos.x + 0x100000;
        hi.y = shell->pos.y + 0x40000;
        hi.z = shell->pos.z + 0x100000;
        func_80070D5C(&lo, &hi, 512, 0x20000);
    } else {
        shell->pos = next;
    }
}

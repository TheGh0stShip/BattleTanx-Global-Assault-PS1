typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct SVec {
    short x;
    short y;
    short z;
    short pad;
} SVec;

typedef struct LightDef {
    int life;
    short radius;
    unsigned short intensity;
    short grow;
    unsigned char color_min[3];
    unsigned char color_max[3];
    short shrink;
    short lerp_color;
    short fixed_scale;
    short pad[3];
} LightDef;

typedef struct Light {
    int pad0;
    short pad4;
    short radius;
    int type;
    int life;
    int timer;
    Vec pos;
    SVec dir;
    SVec axis;
    unsigned short intensity;
    short grow;
    unsigned char color[3];
    unsigned char color_start[3];
    unsigned char attached;
} Light;

extern LightDef D_800AE184[];
extern Light *func_800237D0(int, int);
extern void func_800717F8(SVec *, SVec *);
extern unsigned int func_80086C84(void);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

void func_800718A4(int type, Vec *pos, SVec *dir, int scale, int attached) {
    Light *light;
    int t;
    short v;

    light = func_800237D0(68, 60);
    if (light == 0) {
        return;
    }
    t = scale;
    if (D_800AE184[type].fixed_scale == 0) {
        scale = 4096;
    }
    light->pos = *pos;
    light->attached = attached;
    if (dir == 0 || (dir->x == 0 && dir->y == 0 && dir->z == 0)) {
        light->dir.y = 4096;
        light->dir.z = 0;
        light->dir.x = 0;
        light->axis.z = 4096;
        light->axis.y = 0;
        light->axis.x = 0;
    } else {
        light->dir = *dir;
        func_800717F8(&light->dir, &light->axis);
    }
    light->type = type;
    light->timer = light->life = fixed_mul(D_800AE184[type].life, scale);
    if (D_800AE184[type].shrink) {
        v = fixed_mul(-D_800AE184[type].grow, scale);
        light->grow = v;
        light->radius = fixed_mul(D_800AE184[type].radius, scale) + fixed_mul(-v, light->life);
    } else {
        light->grow = fixed_mul(D_800AE184[type].grow, scale);
        light->radius = fixed_mul(D_800AE184[type].radius, scale);
    }
    light->intensity = D_800AE184[type].intensity;
    if (D_800AE184[type].lerp_color) {
        light->color[0] = D_800AE184[type].color_min[0] + fixed_mul(D_800AE184[type].color_max[0] - D_800AE184[type].color_min[0], t);
        light->color[1] = D_800AE184[type].color_min[1] + fixed_mul(D_800AE184[type].color_max[1] - D_800AE184[type].color_min[1], t);
        light->color[2] = D_800AE184[type].color_min[2] + fixed_mul(D_800AE184[type].color_max[2] - D_800AE184[type].color_min[2], t);
    } else {
        light->color[0] = D_800AE184[type].color_min[0] + ((int)((func_80086C84() >> 16) * (D_800AE184[type].color_max[0] - D_800AE184[type].color_min[0] + 1)) >> 16);
        light->color[1] = D_800AE184[type].color_min[1] + ((int)((func_80086C84() >> 16) * (D_800AE184[type].color_max[1] - D_800AE184[type].color_min[1] + 1)) >> 16);
        light->color[2] = D_800AE184[type].color_min[2] + ((int)((func_80086C84() >> 16) * (D_800AE184[type].color_max[2] - D_800AE184[type].color_min[2] + 1)) >> 16);
    }
    light->color_start[0] = light->color[0];
    light->color_start[1] = light->color[1];
    light->color_start[2] = light->color[2];
}

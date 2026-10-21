typedef struct {
    char pad0[4];
    short type;
} Object;
typedef struct {
    Object *obj;
    char pad4[32];
} Found;
typedef struct {
    char pad0[16];
    int speed;
    int dx;
    int dz;
    char pad1C[12];
} HitSource;
typedef struct {
    int kind;
    char pad4[28];
} HitInfo;
typedef struct {
    char pad0[4];
    short effect;
    char pad6[58];
} HitResult;
typedef struct {
    int unused;
    void (*hit)(Object *, HitResult *, int, HitSource *, HitInfo *);
    int pad8;
} ObjectClass;
typedef struct {
    char pad0[0x2B8];
    unsigned short box;
} Tank;
extern short D_800C628C;
extern ObjectClass D_800D32F4[];
extern unsigned short func_80017AAC(unsigned short, int, Found *, int, int);

static inline int hit_objects(unsigned short box, int mask) {
    Found found[8];
    HitSource src;
    HitInfo info;
    HitResult result;
    int count;
    int i;
    ObjectClass *cls;
    short type;

    D_800C628C = 0;
    count = func_80017AAC(box, mask, found, 0, 0);
    for (i = 0; i < count; i++) {
        if (found[i].obj == 0) {
            continue;
        }
        type = found[i].obj->type;
        if (type != 17 && type != 11) {
            continue;
        }
        info.kind = 2;
        src.speed = 30000;
        src.dx = 0;
        src.dz = 0;
        result.effect = 39;
        type = found[i].obj->type;
        cls = &D_800D32F4[type];
        if (cls->hit != 0 && type != -1) {
            cls->hit(found[i].obj, &result, 0, &src, &info);
        }
    }
    return count;
}

int func_80042F34(Tank *tank, int mask) {
    return hit_objects(tank->box, mask);
}

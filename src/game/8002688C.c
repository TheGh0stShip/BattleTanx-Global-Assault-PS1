typedef struct {
    int flags;
    int timer;
    char pad08[0x20 - 8];
    unsigned short frame;
    char pad22[0x28 - 0x22];
} Sprite;

typedef struct {
    char pad0[0xE];
    unsigned short frame;
} Anim;

typedef struct {
    char pad0[8];
    Anim *anim;
} Model;

typedef struct {
    char pad0[0x3C];
    Model *model;
} Instance;

typedef struct {
    char pad0[6];
    unsigned short sprite;
    char pad08[0x17 - 8];
    unsigned char state;
    char pad18[0x28 - 0x18];
    Model *model;
    char pad2C[0x34 - 0x2C];
    Instance *instance;
    char pad38[2];
    short link;
} Object;

extern Sprite D_800C62B0[];

static inline Sprite *sprite_get(int id) {
    return &D_800C62B0[id];
}

void func_8002688C(Object *obj) {
    register Sprite *sprites asm("$5");
    register int state asm("$2");

    if (obj->link != -1) {
        state = 7;
        sprites = D_800C62B0;
        obj->state = state;
        obj->instance->model = obj->model;
        sprites[obj->sprite].flags |= 0x02000040;
    } else {
        state = 7;
        sprites = D_800C62B0;
        obj->state = state;
        obj->instance->model = obj->model;
        sprites[obj->sprite].timer = 0;
        sprites[obj->sprite].flags |= 0x40;
    }
    sprites[obj->sprite].flags &= ~2;
    sprites[obj->sprite].frame = obj->model->anim->frame;
}

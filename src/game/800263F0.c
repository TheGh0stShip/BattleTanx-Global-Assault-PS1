typedef struct {
    int x;
    int y;
    int z;
} Vector;

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
} Entry;

typedef struct {
    char pad0[0x20];
    unsigned short frame;
    char pad22[0x28 - 0x22];
} Sprite;

typedef struct {
    short pad0;
    unsigned short shape;
    unsigned short models[7];
    char pad12;
    unsigned char animated;
} CrateDef;

typedef struct {
    char pad0[6];
    unsigned short sprite;
    Vector pos;
    unsigned short angle;
    signed char health;
    unsigned char state;
    Model *models[7];
    Entry *entry;
    short timer;
    short link;
    short node;
    short node_id;
} Crate;

extern Sprite D_800C62B0[];
static inline Sprite *sprite_get(int id) {
    return &D_800C62B0[id];
}

extern Crate *func_800237D0(int, int);
extern void *func_80026300(void *, int);
extern Entry *func_8002618C(void *, void *, Vector *, unsigned short, int, unsigned char, unsigned char);
extern unsigned short func_80024C38(void *, Vector *, unsigned short, void *, int, Crate *);

Crate *func_800263F0(CrateDef *def, void *list, Vector *pos, unsigned short angle) {
    Crate *c = func_800237D0(13, 64);
    void *shape;

    if (c == 0) {
        return 0;
    }
    c->state = 0;
    c->timer = 0;
    c->pos = *pos;
    c->angle = angle;
    c->health = 15;
    shape = func_80026300(list, def->shape);
    c->models[0] = func_80026300(list, def->models[0]);
    c->models[1] = func_80026300(list, def->models[1]);
    c->models[2] = func_80026300(list, def->models[2]);
    c->models[3] = func_80026300(list, def->models[3]);
    c->models[4] = func_80026300(list, def->models[4]);
    c->models[5] = func_80026300(list, def->models[5]);
    c->models[6] = func_80026300(list, def->models[6]);
    c->entry = func_8002618C(list, shape, pos, angle, 2, 240, 1);
    c->sprite = func_80024C38(list, pos, angle, shape, 2, c);
    c->link = -1;
    if (def->animated != 0) {
        c->state = 5;
        c->entry->model = c->models[1];
        sprite_get(c->sprite)->frame = c->models[1]->anim->frame;
    }
    c->node = 0;
    c->node_id = -1;
    return c;
}

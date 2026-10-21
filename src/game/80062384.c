typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;

typedef struct Camera {
    int pad[2];
    Vector pos;
} Camera;

typedef struct Object {
    char pad[0x5C];
    Camera *camera;
    char pad2[0x114 - 0x60];
} Object;

typedef struct Blip {
    short x;
    short y;
    unsigned short flags;
    unsigned char alpha;
    char pad;
} Blip;

typedef struct BlipList {
    Blip blips[42];
} BlipList;

extern Object D_800E3E68[];
extern BlipList D_800E4D70[];
extern int func_8006218C(Vector *pos, int *out, int index);
extern unsigned short func_8006186C(unsigned short slot);

static inline int to_int(int x) {
    int r;
    int t = x;

    if (t >= 0) {
        r = t >> 12;
    } else {
        r = -(-t >> 12);
    }
    return r;
}

static inline Object *get_object(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

int func_80062384(Vector *pos, unsigned short index, unsigned short player, unsigned short slot, unsigned short flags) {
    Object *object;
    Camera *camera;
    unsigned short dist;
    int screen[4];

    object = get_object(index);
    camera = object->camera;
    dist = ((to_int(camera->pos.x - pos->x) >= 0 ? to_int(camera->pos.x - pos->x) : -to_int(camera->pos.x - pos->x)) > (to_int(camera->pos.z - pos->z) >= 0 ? to_int(camera->pos.z - pos->z) : -to_int(camera->pos.z - pos->z)) ? (to_int(camera->pos.x - pos->x) >= 0 ? to_int(camera->pos.x - pos->x) : -to_int(camera->pos.x - pos->x)) : (to_int(camera->pos.z - pos->z) >= 0 ? to_int(camera->pos.z - pos->z) : -to_int(camera->pos.z - pos->z))) + ((to_int(camera->pos.x - pos->x) >= 0 ? to_int(camera->pos.x - pos->x) : -to_int(camera->pos.x - pos->x)) < (to_int(camera->pos.z - pos->z) >= 0 ? to_int(camera->pos.z - pos->z) : -to_int(camera->pos.z - pos->z)) ? (to_int(camera->pos.x - pos->x) >= 0 ? to_int(camera->pos.x - pos->x) : -to_int(camera->pos.x - pos->x)) : (to_int(camera->pos.z - pos->z) >= 0 ? to_int(camera->pos.z - pos->z) : -to_int(camera->pos.z - pos->z))) * 3 / 8;
    if (!(flags & 0xF0)) {
        if (dist <= 20000) {
            goto ok;
        }
        return 0;
    }
    if ((unsigned short)(dist - 4000) > 24000) {
        goto fail;
    }
ok:
    if (func_8006218C(pos, screen, index) == 0) {
        goto fail;
    }
    D_800E4D70[index].blips[slot].x = screen[0];
    if (index != 0) {
        D_800E4D70[index].blips[slot].y = screen[1] + 120;
    } else {
        D_800E4D70[index].blips[slot].y = screen[1];
    }
    D_800E4D70[index].blips[slot].flags = func_8006186C(player);
    D_800E4D70[index].blips[slot].alpha = 254;
    D_800E4D70[index].blips[slot].flags |= flags;
    return 1;
fail:
    return 0;
}

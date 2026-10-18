typedef struct { int x, y, z; } Vector;
typedef struct { char pad[12]; int team; char rest[0x114 - 16]; } Waypoint;
typedef struct {
    short pad;
    short pad1;
    short pad2;
    unsigned short cell;
    Vector pos;
    unsigned short angle;
    unsigned char waypoint;
    char pad3;
    short hp;
    short pad4;
    int pad5;
    int model;
} Wall;
typedef struct { int pad; short type; } Msg;
typedef struct { int zero; int pad[2]; int drain; unsigned short amount; short pad2; Waypoint *source; } Data;
typedef struct { unsigned char valid; char pad[3]; int x; int z; } Query;
extern Waypoint D_800E3E68[];
void func_800531D4(Waypoint *, int);
void func_80035948(int, Vector *, int, int, int, int, int, int);
void func_80031F20(Wall *, Msg *, Data *, void *);

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline void damage(Wall *w, int amount) {
    if (w->hp > 0) {
        w->hp -= amount;
        if (w->hp <= 0) {
            func_80035948(w->model, &w->pos, w->angle, 0, 0, 0, 0, 0);
        }
    }
}

void func_800320A0(Wall *wall, Msg *msg, unsigned int event, Data *data, int *out) {
    Wall *w = wall;

    switch (event) {
    case 0:
        switch (msg->type) {
        case 12:
        case 39:
        case 40:
        case 52:
            if (data->source != 0 && data->source->team == waypoint_at(w->waypoint)->team) {
                func_800531D4(data->source, 7);
            } else {
                func_800531D4(waypoint_at(w->waypoint), 10);
            }
            damage(w, data->amount);
            *out = 1;
            break;
        default:
            *out = 1;
            break;
        }
        break;
    case 5:
        if (data->zero == 0 && w->hp != 0) {
            ((Query *)out)->valid = 2;
            ((Query *)out)->x = w->pos.x;
            ((Query *)out)->z = w->pos.z;
        }
        break;
    case 6:
        func_80031F20(w, msg, data, out);
        break;
    case 3:
        damage(w, data->drain);
        func_800531D4(waypoint_at(w->waypoint), 10);
        break;
    }
}

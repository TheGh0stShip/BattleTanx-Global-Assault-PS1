typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Track {
    int dist;
    char pad04[4];
    int best;
    int timer;
    unsigned char seen;
    unsigned char mode;
    char pad12[2];
    void *target;
} Track;
typedef struct TrackThing {
    char pad00[4];
    short type;
    char pad06[2];
    Vector position;
    char pad14[4];
    short hp;
} TrackThing;
typedef struct TrackTeam {
    char pad00[0xC];
    int team;
} TrackTeam;
typedef struct TrackTank {
    int id;
    char pad004[4];
    Vector position;
    Vector last;
    char pad020[0xA8 - 0x20];
    int bit;
    int seen;
    char pad0B0[0xB8 - 0xB0];
    Track track;
    char pad0D0[0xF0 - 0xD0];
    unsigned char valid;
    unsigned char kind;
    char pad0F2[0x170 - 0xF2];
    Vector eye;
    char pad17C[0x180 - 0x17C];
    int status;
    char pad184[0x208 - 0x184];
    TrackTeam *owner;
} TrackTank;
typedef struct ProbeHit {
    char pad[0x24];
} ProbeHit;
extern short D_800C628C;
extern int D_800D2FE0;
extern int D_800DE30C;
int func_80047658(TrackTank *);
int func_80047688(TrackTank *);
void func_8004E0BC(TrackTank *);
int func_800495D8(Vector *, Vector *);
unsigned short func_80019D80(Vector *, Vector *, int, int, int, ProbeHit *);
void func_8004E610(TrackTank *, Vector *);

void func_8004D9FC(TrackTank *tank) {
    Vector *pos = 0;
    int visible = 0;
    int lost = 0;
    int mask = 0x2C7007;
    Track *track = &tank->track;
    ProbeHit hit;
    int dist;

    switch (track->mode) {
    case 1: {
        TrackTank *other = track->target;
        if (!func_80047658(other) || !func_80047688(other)) {
            func_8004E0BC(tank);
            lost = 1;
            break;
        }
        pos = &other->eye;
        if (tank->seen & other->bit) {
            visible = 1;
            break;
        }
        if (tank->owner->team != other->owner->team) {
            lost = 1;
        }
        break;
    }
    case 0:
        lost = 1;
        break;
    case 3: {
        TrackThing *thing = track->target;
        if (thing == 0 || thing->type != 30 || thing->hp <= 0) {
            func_8004E0BC(tank);
        } else {
            pos = &thing->position;
            mask = 0x287007;
        }
        break;
    }
    case 2:
        pos = (Vector *)&track->target;
        if (pos != 0 && tank->kind == 5) {
            visible = tank->valid != 0;
        }
        lost = !visible;
        break;
    }
    if (pos == 0) {
        track->best = 64000 << 12;
        tank->status &= ~2;
        tank->status &= ~1;
        return;
    }
    dist = func_800495D8(pos, &tank->position);
    if (lost && track->seen) {
        tank->status &= ~2;
        tank->status &= ~1;
    } else {
        if (!visible && !lost) {
            D_800C628C = 0;
            lost = func_80019D80(&tank->position, pos, mask, 0, tank->id, &hit);
            visible = !lost;
        }
        if (lost && track->seen) {
            tank->status &= ~2;
            tank->status &= ~1;
        } else {
            if (dist < track->dist) {
                tank->status |= 1;
            } else {
                tank->status &= ~1;
            }
            if (visible) {
                tank->status |= 2;
            } else {
                tank->status &= ~2;
            }
        }
    }
    if (tank->status & 2) {
        track->best = 64000 << 12;
        track->timer = D_800D2FE0 + 300;
        return;
    }
    if (func_800495D8(pos, &tank->last) < dist) {
        track->timer += D_800DE30C;
    } else if (dist < track->best) {
        track->best = dist;
        track->timer = D_800D2FE0 + 300;
    } else if (D_800D2FE0 >= track->timer) {
        track->timer = D_800D2FE0 + 300;
        func_8004E610(tank, pos);
    }
}

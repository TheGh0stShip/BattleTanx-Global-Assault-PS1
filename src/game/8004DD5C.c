typedef struct Track {
    int dist;
    int hit;
    int best;
    int timer;
    unsigned char seen;
    unsigned char mode;
    char pad12[2];
    struct ScanTank *target;
} Track;
typedef struct ScanTeam {
    char pad00[0xC];
    int team;
} ScanTeam;
typedef struct Waypoint {
    char pad000[0xC];
    int team;
    char pad010[0x114 - 0x10];
} Waypoint;
typedef struct ScanTank {
    char pad000[0xB8];
    Track track;
    char pad0D0[0x180 - 0xD0];
    int status;
    char pad184[0x1F4 - 0x184];
    int weapon;
    char pad1F8[0x208 - 0x1F8];
    ScanTeam *owner;
    char pad20C[0x218 - 0x20C];
    int flags;
} ScanTank;
extern Waypoint D_800E3E68[];
extern int D_800D2FE0;
int func_80047688(ScanTank *);
void *func_80052F9C(Waypoint *, int, int, int);
void func_8004E0FC(ScanTank *, void *, int, int);

static inline Waypoint *waypoint_at(int index) {
    return &D_800E3E68[index];
}

static inline Waypoint *waypoint(int index) {
    if (index == 127) {
        return 0;
    }
    return waypoint_at(index);
}

static inline void *scan_targets(int team) {
    void *result = 0;
    unsigned short i;

    for (i = 0; i < 5; i++) {
        Waypoint *candidate = waypoint(i);
        if (candidate->team == team) {
            continue;
        }
        if ((result = func_80052F9C(candidate, 0, 3, 1)) != 0) {
            break;
        }
        if ((result = func_80052F9C(candidate, 0, 1, 1)) != 0) {
            break;
        }
    }
    return result;
}

void func_8004DD5C(ScanTank *tank) {
    void *result;

    if (tank->track.mode == 1 && tank->track.target != 0) {
        if (tank->track.target->flags & 1) {
            if (func_80047688(tank->track.target)
                && tank->track.target->owner->team != tank->owner->team) {
                if (tank->track.target->flags & 2) {
                    return;
                }
                result = scan_targets(tank->owner->team);
                if (result == 0) {
                    return;
                }
                func_8004E0FC(tank, result, tank->weapon, 1);
                return;
            }
        }
    }
    result = scan_targets(tank->owner->team);
    if (result == 0) {
        Track *track = &tank->track;
        int best = 64000 << 12;
        int timer = D_800D2FE0 + 300;

        tank->track.dist = 0;
        track->hit = 0;
        track->best = best;
        track->seen = 0;
        track->mode = 0;
        track->timer = timer;
        tank->status &= ~1;
        return;
    }
    func_8004E0FC(tank, result, tank->weapon, 1);
}

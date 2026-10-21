typedef struct { char pad[12]; int team; char rest[0x114 - 16]; } Waypoint;
typedef struct Node Node;
struct Node { short pad; short next; int pad2[2]; int active; char rest[48]; };
typedef struct { int pad[3]; int team; } Owner;
typedef struct Marker Marker;
typedef struct { int id; char pad[160]; Marker *markers; char pad2[520 - 168]; Waypoint *home; } Tank;
struct Marker { int pad[3]; int state; int pad2[2]; int owner; Marker *next; char pad3[16]; unsigned char waypoint; };
typedef struct { int pad; unsigned int mode; unsigned char teams; } Rules;
extern unsigned int D_800D2FE8;
extern Rules D_800D2FE4;
extern short D_800D3270;
extern Node *D_800D3258;
extern int D_800D3028;
extern Waypoint D_800E3E68[];
void func_800531D4(Waypoint *, int);

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80032E1C(Tank *owner, Marker *m) {
    Tank *tank = owner;
    int i;
    int found;
    int k;
    Node *n;

    switch (D_800D2FE8) {
    case 1:
    case 2:
    case 3:
    case 11:
        func_800531D4(tank->home, 5);
        if (m->waypoint != 127) {
            func_800531D4(waypoint_at(m->waypoint), 6);
        } else {
            for (i = 0; i < D_800D2FE4.teams; i++) {
                if (waypoint_at(i)->team != tank->home->team) {
                    func_800531D4(waypoint_at(i), 6);
                }
            }
        }
        break;
    case 14:
        found = 0;
        n = &D_800D3258[D_800D3270];
        while (1) {
            if (n != (Node *)m && n->active == 1) {
                found = 1;
                break;
            }
            if (n->next == -1) {
                break;
            }
            n = &D_800D3258[n->next];
        }
        if (!found) {
            func_800531D4(tank->home, 11);
        } else {
            switch (D_800D3028) {
            case 14:
                func_800531D4(tank->home, 0);
                break;
            case 33:
                func_800531D4(tank->home, 8);
                break;
            }
        }
        break;
    }
    m->next = tank->markers;
    tank->markers = m;
    m->state = 2;
    m->owner = tank->id;
}

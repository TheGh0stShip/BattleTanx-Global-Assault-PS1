typedef struct {
    char pad[0x114];
} Waypoint;

typedef struct {
    char pad0[6];
    unsigned char state;
    char pad7[0x14 - 7];
    unsigned char target;
    char pad15[0x1C - 0x15];
    int timer;
} Event;

extern Waypoint D_800E3E68[];
extern int func_8006C2D4(Waypoint *w);
extern void func_80052A24(Waypoint *w, int arg);
extern int func_80052CE4(Waypoint *w);

static inline Waypoint *waypoint(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_8006B050(Event *ev, int *done) {
    int arg;
    Event *e = ev;

    switch (ev->state) {
    case 1:
        ev->timer++;
        if (ev->timer >= 46) {
            arg = func_8006C2D4(waypoint(ev->target));
            func_80052A24(waypoint(e->target), arg);
            *done = 1;
        }
        break;
    case 0:
        break;
    case 2:
        ev->timer++;
        if (ev->timer >= 46) {
            if (func_80052CE4(waypoint(ev->target)) >= 0) {
                *done = 1;
            }
        }
        break;
    }
}

typedef struct { int pad; unsigned short count; } Counter;
typedef struct { char pad[6]; unsigned char flags; char pad2[5]; Counter *counter; char rest[0x114 - 16]; } Waypoint;
typedef struct { char pad[212]; unsigned short carried; } Home;
typedef struct { char pad[24]; unsigned char waypoint; } Base;
typedef struct {
    char pad[152];
    int team;
    char pad2[520 - 156];
    Waypoint *home;
    char pad3[536 - 524];
    unsigned int status;
} Tank;
typedef struct { int pad; short type; short pad2; Tank *tank; } Msg;
typedef struct {
    int pad[2];
    int kind;
    int state;
    int pad2;
    Base *base;
    char pad3[48 - 24];
    unsigned char pad4;
    unsigned char waypoint;
    unsigned short sound;
} Flag;
typedef struct { int pad; unsigned int mode; unsigned char teams; unsigned char limit; char pad2[58]; int sub; } Rules;
extern Rules D_800D2FE4;
extern Waypoint D_800E3E68[];
extern char D_800BE29C[];
extern char D_800BE2AC[];
int func_80022814(Flag *);
void func_8001B094(int);
void func_800531D4(Waypoint *, int);
void func_8008AFB0(char *, char *, ...);
void func_80063018(int, char *, int);
void func_80032C18(void);
void func_80033FD4(Base *, Flag *);
void func_80032E1C(Tank *, Flag *);

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline void open_gates(Flag *f) {
    int i;
    Waypoint *wp;

    if (f->waypoint != 127) {
        waypoint_at(f->waypoint)->flags |= 4;
    } else {
        for (i = 0; i < D_800D2FE4.limit; i++) {
            wp = waypoint_at(i);
            if ((wp->flags & 2) == 0) {
                wp->flags |= 4;
            }
        }
    }
}

void func_80033044(Flag *f, Msg *msg) {
    register Tank *t asm("$16");
    char buf[128];

    if (msg->type != 4) {
        return;
    }
    t = msg->tank;
    if (f->kind == 2) {
        if (func_80022814(f) != 0 && t->team >= D_800D2FE4.teams) {
            return;
        }
        func_8001B094(f->sound);
        f->sound = 0xFFFF;
        waypoint_at(t->team)->counter->count++;
        f->state = 3;
        if (D_800D2FE4.mode == 13) {
            switch (D_800D2FE4.sub) {
            case 28:
                func_800531D4(t->home, 0);
                break;
            case 9:
            case 24:
                func_800531D4(t->home, 8);
                break;
            case 4:
                func_800531D4(t->home, 13);
                break;
            case 20:
                func_800531D4(t->home, 5);
                break;
            }
        }
        if (D_800D2FE4.mode == 2) {
            if (waypoint_at(t->team)->counter->count == 1) {
                func_8008AFB0(buf, D_800BE29C);
            } else {
                func_8008AFB0(buf, D_800BE2AC, waypoint_at(t->team)->counter->count);
            }
            func_80063018((unsigned short)t->team, buf, 45);
            func_80032C18();
            return;
        }
        open_gates(f);
        return;
    }
    if (D_800D2FE4.mode == 14 && (t->status & 2) == 0) {
        return;
    }
    if (f->state == 0) {
        if (waypoint_at(f->base->waypoint)->counter == t->home->counter) {
            return;
        }
        func_80033FD4(f->base, f);
        waypoint_at(f->base->waypoint)->counter->count--;
    }
    func_8001B094(f->sound);
    f->sound = 0xFFFF;
    func_80032E1C(t, f);
    if (D_800D2FE4.mode == 14) {
        ((Home *)t->home)->carried++;
    }
    open_gates(f);
}

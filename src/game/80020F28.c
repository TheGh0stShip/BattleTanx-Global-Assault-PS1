typedef struct {
    unsigned short score;
    char pad2[2];
    unsigned short kills;
    char pad6[2];
    int value;
    char padC[0x24 - 0xC];
} Team;

typedef struct {
    char pad0[6];
    unsigned char flags;
    char pad7[0xC - 7];
    Team *team;
    char pad10[0x58 - 0x10];
    int result;
    char pad5C[0x70 - 0x5C];
    int score;
    char pad74[0x114 - 0x74];
} Waypoint;

typedef struct {
    char pad0[0x68];
    int limit;
} Level;

typedef struct {
    void *screen;
    int mode;
    unsigned char players;
    unsigned char count;
    unsigned char teams;
    char padB[5];
    int timer;
    int timer2;
    char pad18[0x40 - 0x18];
    Level *level;
} Globals;

extern Globals D_800D2FE4;
extern int D_800D2FE0;
extern int D_800D2FC4;
extern int D_800C60D8;
extern Team D_800E3DB4[];
extern Waypoint D_800E3E68[];
extern void func_800531D4(Waypoint *, int);
extern void func_80052DB4(Waypoint *);

static inline Waypoint *waypoint_get(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline int fixed_to_int(int value) {
    if (value >= 0) {
        return value >> 12;
    }
    return -(-value >> 12);
}

static inline void notify_all(int msg) {
    int i;

    for (i = 0; i < D_800D2FE4.players; i++) {
        func_800531D4(waypoint_get(i), msg);
    }
}

static inline int team_total(Team *team) {
    int sum = 0;
    int j;
    Waypoint *v;

    for (j = 0; j < D_800D2FE4.count; j++) {
        v = waypoint_get(j);
        if (v->team == team) {
            sum += v->score;
        }
    }
    return sum;
}

static inline int check_alive(void) {
    int alive = 0;
    int i;
    Waypoint *w;

    if (D_800C60D8 < 120) {
        return 0;
    }
    for (i = 0; i < D_800D2FE4.count; i++) {
        w = waypoint_get(i);
        func_80052DB4(w);
        if (w->result != 2 && (w->flags & 2)) {
            alive++;
        }
    }
    return (alive == 0) * 2;
}

static inline int check_survivors(void) {
    int others = 0;
    int done = 0;
    int i;
    Waypoint *w;

    if (D_800C60D8 < 120) {
        return 0;
    }
    for (i = 0; i < D_800D2FE4.count; i++) {
        w = waypoint_get(i);
        func_80052DB4(w);
        if (w->result != 2) {
            if (w->flags & 2) {
                others++;
            } else {
                done++;
            }
        }
    }
    if (others == 0 || done == 0) {
        return 2;
    }
    return 0;
}

int func_80020F28(void) {
    int done = 0;
    int i;
    int best;
    int sum;
    int now;
    Waypoint *w;
    Waypoint *leader;

    switch (D_800D2FE4.mode) {
    case 5:
        if (D_800D2FE0 > D_800D2FE4.timer) {
            best = -1;
            for (i = 0; i < D_800D2FE4.teams; i++) {
                int total = team_total(&D_800E3DB4[i]);
                if (best < total) {
                    best = total;
                }
            }
            for (i = 0; i < D_800D2FE4.count; i++) {
                sum = team_total(waypoint_get(i)->team);
                if (sum == best) {
                    waypoint_get(i)->result = 1;
                } else {
                    waypoint_get(i)->result = 2;
                }
            }
            return 1;
        }
        now = D_800D2FE0;
        if (D_800D2FE4.timer - now < 600 && D_800D2FE4.timer - D_800D2FC4 >= 600) {
            notify_all(3);
        } else if (D_800D2FE4.timer - now < 1800 && D_800D2FE4.timer - D_800D2FC4 >= 1800) {
            notify_all(2);
        }
        D_800D2FC4 = now;
        break;
    case 0:
    case 6:
        for (i = 0; i < D_800D2FE4.teams; i++) {
            if (D_800E3DB4[i].score >= D_800D2FE4.timer) {
                return 2;
            }
        }
        break;
    case 3:
        for (i = 0; i < D_800D2FE4.teams; i++) {
            if (fixed_to_int(D_800E3DB4[i].value) >= D_800D2FE4.timer) {
                done = 1;
            }
        }
        if (done) {
            for (i = 0; i < D_800D2FE4.count; i++) {
                w = waypoint_get(i);
                if (fixed_to_int(w->team->value) >= D_800D2FE4.timer) {
                    w->result = 1;
                } else {
                    w->result = 2;
                }
            }
            return 1;
        }
        break;
    case 1:
    case 2:
    case 11:
    case 13:
        for (i = 0; i < D_800D2FE4.teams; i++) {
            if (D_800E3DB4[i].kills >= D_800D2FE4.timer) {
                done = 1;
            }
        }
        if (done) {
            for (i = 0; i < D_800D2FE4.count; i++) {
                w = waypoint_get(i);
                if (w->team->kills >= D_800D2FE4.timer) {
                    w->result = 1;
                } else {
                    w->result = 2;
                }
            }
            return 1;
        }
        if (D_800D2FE4.mode == 11 || D_800D2FE4.mode == 13) {
            done = 1;
            for (i = 0; i < D_800D2FE4.count; i++) {
                w = waypoint_get(i);
                if (w->flags & 2) {
                    func_80052DB4(w);
                    if (w->result != 2) {
                        done = 0;
                    }
                }
            }
            if (done) {
                return 2;
            }
            break;
        }
        break;
    case 12:
        if (D_800D2FE4.timer2 != 0) {
            if (D_800D2FE4.level->limit < D_800D2FE0 - D_800D2FE4.timer2) {
                D_800E3E68[0].result = 1;
            }
        } else if (D_800D2FE4.timer == 0) {
            D_800D2FE4.timer2 = D_800D2FE0;
        }
    case 7:
    case 10:
    case 14:
        leader = D_800E3E68;
        if (leader->result == 1) {
            for (i = 0; i < D_800D2FE4.count; i++) {
                w = waypoint_get(i);
                if (w->team == leader->team) {
                    w->result = 1;
                } else {
                    w->result = 2;
                }
            }
            return 1;
        }
        if (leader->result == 2) {
            for (i = 0; i < D_800D2FE4.count; i++) {
                w = waypoint_get(i);
                if (w->team == leader->team) {
                    w->result = 2;
                } else {
                    w->result = 1;
                }
            }
            return 1;
        }
        return check_alive();
    case 9:
        if (D_800D2FE0 >= D_800D2FE4.timer) {
            leader = D_800E3E68;
            for (i = 0; i < D_800D2FE4.count; i++) {
                w = waypoint_get(i);
                if (w->team == leader->team) {
                    w->result = 1;
                } else {
                    w->result = 2;
                }
            }
            return 1;
        }
        leader = D_800E3E68;
        if (leader->result == 2) {
            for (i = 0; i < D_800D2FE4.count; i++) {
                w = waypoint_get(i);
                if (w->team == leader->team) {
                    w->result = 2;
                } else {
                    w->result = 1;
                }
            }
            return 1;
        }
        return check_survivors();
    case 8:
        return check_survivors();
    }
    return 0;
}

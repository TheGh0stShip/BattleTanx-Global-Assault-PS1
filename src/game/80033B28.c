typedef struct { int x, y, z; } Vector;
typedef struct { char pad[4]; unsigned char slot; } Owner;
typedef struct { char pad[20]; unsigned char team; } Squad;
typedef struct { char pad[24]; int ids[1]; } Roster;
typedef struct {
    int pad;
    unsigned int mode;
    unsigned char teams;
    unsigned char limit;
    char pad2[42];
    unsigned char team_of[5];
    unsigned char unit_of[7];
    Roster *roster;
} Rules;
typedef struct {
    int pad[2];
    Vector pos;
    short kind;
    short handle;
    unsigned char team;
    unsigned char color;
    char pad2[2];
    int frame;
} Mark;
extern Rules D_800D2FE4;
extern unsigned int D_800A6084[];
extern int D_800D2FBC;
Mark *func_800237D0(int, int);
int func_80022814(void);
Squad *func_80053338(int);
short func_80024C38(int, Vector *, int, int, int, Mark *);

static inline int team_mode(void) {
    switch (D_800D2FE4.mode) {
    case 1:
    case 3:
    case 11:
        return 1;
    }
    return 0;
}

void func_80033B28(Owner *owner, int id, Vector *pos, short kind) {
    int team;
    Mark *m;

    if (team_mode()) {
        team = D_800D2FE4.team_of[owner->slot];
        if (team < D_800D2FE4.limit) {
            m = func_800237D0(22, 32);
            if (m != 0) {
                m->pos = *pos;
                m->kind = kind;
                m->team = team;
                if (func_80022814() != 0) {
                    m->color = func_80053338(D_800D2FE4.roster->ids[D_800D2FE4.unit_of[team]])->team;
                } else {
                    switch (D_800A6084[team]) {
                    case 1:
                        m->color = 2;
                        break;
                    case 2:
                        m->color = 3;
                        break;
                    case 3:
                        m->color = 4;
                        break;
                    case 4:
                        m->color = 1;
                        break;
                    }
                }
                m->frame = D_800D2FBC;
                m->handle = func_80024C38(id, pos, (unsigned short)kind, m->frame, 1, m);
            }
        }
    }
}

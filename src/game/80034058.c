typedef struct { int pad; unsigned short count; } Counter;
typedef struct { char pad[12]; Counter *counter; char pad2[212 - 16]; unsigned short alive; } Owner;
typedef struct Item Item;
struct Item { int pad[7]; Item *next; };
typedef struct { char pad[152]; int team; int pad2[2]; Item *items; char pad3[520 - 168]; Owner *owner; } Tank;
typedef struct { int pad; short type; short pad2; Tank *tank; char pad3[10]; unsigned char waypoint; } Msg;
typedef struct { char pad[88]; int captured; char rest[0x114 - 92]; } Waypoint;
typedef struct { int pad; unsigned int mode; unsigned char teams; char pad2[7]; int goal; } Rules;
typedef struct { short pad[3]; unsigned char done; char pad2[21]; int score; } Goal;
extern Rules D_800D2FE4;
extern int D_800AAF40;
extern Waypoint D_800E3E68[];
void func_80022840(void);
void func_800228B0(void);

static inline Waypoint *waypoint_at(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

void func_80034058(Goal *g, Msg *msg) {
    Tank *t;

    switch (D_800D2FE4.mode) {
    case 14:
        if (msg->type == 4) {
            t = msg->tank;
            if (t->team < D_800D2FE4.teams && g->done == 0) {
                while (t->items != 0) {
                    t->items = t->items->next;
                    g->score++;
                    t->owner->alive--;
                }
                D_800AAF40 = g->score;
                if (g->score >= D_800D2FE4.goal) {
                    func_80022840();
                }
            }
        }
        break;
    case 7:
    case 9:
        if (msg->type == 4) {
            t = msg->tank;
            if (t->team < D_800D2FE4.teams) {
                if (g->done == 0 && t->owner->counter->count >= D_800D2FE4.goal) {
                    func_80022840();
                }
            } else if (g->done != 0) {
                func_800228B0();
            }
        }
        break;
    case 4:
    case 10:
        if (msg->type == 30) {
            waypoint_at(msg->waypoint)->captured = 1;
        }
        break;
    }
}

typedef struct {
    char pad0[0xE076];
    unsigned short blink_color;
} System;
typedef struct {
    int op;
    void *fn;
    unsigned short arg;
    short padA;
} Command;
typedef struct {
    char pad0[0x14];
    unsigned int state;
    Command cmds[4];
    unsigned short count;
    short pad4A;
    int timer;
    unsigned short color;
    unsigned char blink;
} Marker;
extern System *D_800A5B24;
extern int D_800D2FE8;
extern int D_800D2FE0;
extern void func_80050E90(void);

static inline void push(Marker *m, int op, void *fn, unsigned short arg) {
    Command *c = &m->cmds[m->count];

    c->op = op;
    c->arg = arg;
    c->fn = fn;
    m->count++;
}

int func_80051340(Marker *m, unsigned int state, int *timer, int use_timer) {
    int changed = m->state != state;

    m->state = state;
    m->count = 0;
    switch (state) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        if (use_timer != 0) {
            m->timer = *timer;
        }
        push(m, 19, 0, 16);
        break;
    case 4:
        if (use_timer != 0) {
            m->timer = *timer;
        }
        push(m, 20, func_80050E90, 1);
        push(m, 6, 0, 16);
        break;
    case 5:
        if (use_timer != 0) {
            m->timer = *timer;
        }
        push(m, 18, 0, 16);
        break;
    case 6:
        if (use_timer != 0) {
            m->timer = *timer;
        }
        break;
    case 7:
        m->timer = D_800D2FE0 + 150;
        m->color = D_800A5B24->blink_color;
        m->blink = 0;
        if (D_800D2FE8 == 10) {
            break;
        }
        push(m, 9, 0, 1);
        push(m, 6, 0, 16);
        break;
    }
    return changed;
}

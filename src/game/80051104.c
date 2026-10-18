typedef struct Tank {
    char pad0[0xA8];
    int bits;
    char padAC[0x17C - 0xAC];
    unsigned int state;
} Tank;
typedef struct {
    int op;
    int (*fn)(Tank *, int);
    unsigned short arg;
    short padA;
} Command;
typedef struct {
    char pad0[0x18];
    Command cmds[4];
    unsigned short count;
} Marker;
extern Tank *func_80052F38(Marker *, Tank *);
extern int func_80047658(Tank *);
extern void func_8004E2AC(Tank *, int);

void func_80051104(Marker *m) {
    unsigned short i;
    int used = 0;

    for (i = 0; i < m->count; i++) {
        Command *c = &m->cmds[i];
        unsigned int n = c->arg;
        Tank *best = 0;
        int best_score = 0;
        Tank *t;

        for (t = func_80052F38(m, 0); t != 0; t = func_80052F38(m, t)) {
            if (n == 0) {
                goto next_command;
            }
            if (t->bits & used) {
                continue;
            }
            if (c->fn == 0) {
                int ok = 0;

                if (func_80047658(t) != 0) {
                    switch (t->state) {
                    case 6:
                    case 9:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                        ok = 1;
                        break;
                    default:
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    if (t->state != c->op) {
                        func_8004E2AC(t, c->op);
                    }
                    n--;
                }
                used |= t->bits;
            } else {
                int score = c->fn(t, c->op);

                if (score <= 0) {
                    used |= t->bits;
                    continue;
                }
                if (best_score < score) {
                    Tank *tmp = best;

                    best = t;
                    best_score = score;
                    t = tmp;
                }
                if (n < 2) {
                    continue;
                }
                if (t == 0) {
                    continue;
                }
                if (t->state != c->op) {
                    func_8004E2AC(t, c->op);
                }
                n--;
                used |= t->bits;
            }
        }
        if (n != 0 && best != 0) {
            if (best->state != c->op) {
                func_8004E2AC(best, c->op);
            }
            used |= best->bits;
        }
    next_command:;
    }
}

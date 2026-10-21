typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    char pad0[0xC];
    int team;
} Owner;
typedef struct {
    int id;
    char pad4[0x8 - 0x4];
    Vector position;
    char pad14[0xA8 - 0x14];
    int bit;
    int visible;
    int near;
    char padB4[0x170 - 0xB4];
    Vector eye;
    int state;
    char pad180[0x1F0 - 0x180];
    int range;
    char pad1F4[0x208 - 0x1F4];
    Owner *owner;
    char pad20C[0x218 - 0x20C];
    int status;
    char pad21C[0x598 - 0x21C];
} Tank;
typedef struct {
    int id;
    char pad4[36];
} Hit;
extern Tank D_800DE33C[];
extern unsigned short D_800E3CBC;
extern unsigned char D_800E3CC4[][2];
extern short D_800C628C;
extern int func_800495D8(Vector *, Vector *);
extern unsigned short func_80019D80(Vector *, Vector *, int, int, int, Hit *);
extern int func_80047688(Tank *);

void func_800499AC(void) {
    int close;
    unsigned short i;
    int done;
    Tank *a;
    Tank *b;
    int same;
    int range;
    Hit hit;
    unsigned char *pair;

    close = 0;
    i = 0;
    done = close;
    while (!done) {
        if (i >= 30) {
            break;
        }
        if (++D_800E3CBC >= 120) {
            D_800E3CBC = 0;
        }
        pair = D_800E3CC4[D_800E3CBC];
        a = &D_800DE33C[pair[0]];
        b = &D_800DE33C[pair[1]];
        if (!(a->status & 1) || !(b->status & 1)) {
            a->near &= ~b->bit;
            b->near &= ~a->bit;
            a->visible &= ~b->bit;
            b->visible &= ~a->bit;
            goto next;
        }
        if (a->status & 2) {
            if (b->status & 2) {
                goto next;
            }
        } else if (!(b->status & 2)) {
            close = 1;
        }
        same = a->owner->team == b->owner->team;
        if (same) {
            if (func_800495D8(&a->position, &b->position) > 0x3E8000) {
                a->near &= ~b->bit;
                b->near &= ~a->bit;
                goto next;
            }
        } else {
            range = b->range;
            if (range < a->range) {
                range = a->range;
            }
            if (range <= 0xBB7FFF) {
                if (a->state == 7 || b->state == 7 || a->state == 8 || b->state == 8) {
                    range = 0x1F40000;
                    if (close) {
                        range = 0xBB8000;
                    }
                }
            }
            if (func_800495D8(&a->position, &b->position) > range) {
                goto hide;
            }
        }
        if (same) {
            a->near |= b->bit;
            b->near |= a->bit;
            goto next;
        }
        D_800C628C = 0;
        if (func_80019D80(&a->eye, &b->eye, 0x24100B, 0, a->id, &hit) != 0 && hit.id != b->id) {
            goto hide;
        }
        if (func_80047688(b) == 0) {
            a->visible &= ~b->bit;
        } else {
            a->visible |= b->bit;
        }
        if (func_80047688(a) == 0) {
            b->visible &= ~a->bit;
        } else {
            b->visible |= a->bit;
        }
        goto next;
    hide:
        a->visible &= ~b->bit;
        b->visible &= ~a->bit;
    next:
        i++;
    }
}

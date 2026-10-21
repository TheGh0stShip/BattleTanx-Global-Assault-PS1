typedef struct { int x, y, z; } Vector;
typedef struct { unsigned char b[8]; } Tint;
typedef struct { char pad[32]; Vector pos; int pad2[4]; int value; } Target;
typedef struct { int pad[2]; Target *target; int pad2; int model; int pad3; int state; Vector pos; unsigned short sound; short pad4; unsigned char hit; } Crate;
typedef struct { int pad; unsigned short type; } Msg;
extern Tint D_800BD92C;
void func_800738D4(int, Vector *, int, Tint *, int);
void func_8003BADC(int, int);
unsigned int func_80086C84(void);
void func_80053790(int, int, int);
void func_8001B094(int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_8002CA3C(Crate *c, Msg *msg, int unused, int *out) {
    Tint tint;

    switch ((short)msg->type) {
    case 7:
    case 12:
    case 39:
    case 40:
    case 52:
        if (c->state == 0) {
            if (c->model != 0) {
                tint = D_800BD92C;
                func_800738D4(c->model, &c->pos, 0, &tint, 100);
                func_8003BADC(to_int(c->pos.x), to_int(c->pos.z));
            }
            if (((func_80086C84() >> 16) & 1) == 0) {
                func_80053790(5, c->pos.x, c->pos.z);
            } else {
                func_80053790(51, c->pos.x, c->pos.z);
            }
            c->state = 3;
            func_8001B094(c->sound);
            c->target->value = 0;
            *out = 1;
        }
        break;
    case 4:
        if (c->state == 1) {
            *out = 9;
        } else if (c->state == 0) {
            goto start;
        } else if (c->state == 2) {
            goto opening;
        }
        break;
    start:
        *out = 9;
        c->hit = 0;
        c->state = 1;
        break;
    opening:
        *out = 8;
        break;
    case 30:
        if (c->state == 0) {
            *out = 1;
        }
        break;
    }
}

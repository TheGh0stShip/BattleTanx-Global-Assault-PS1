typedef struct { int x, y, z; } Vector;
typedef struct { unsigned char b[8]; } Tint;
typedef struct { char pad[32]; Vector pos; int pad2[4]; int value; } Target;
typedef struct { int pad[2]; Target *target; int pad2; int model; int pad3; int state; Vector pos; unsigned short sound; } Crate;
typedef struct { unsigned char valid; char pad[3]; int x; int z; } Query;
typedef struct { int x; int z; } Hit2;
extern Tint D_800BD92C;
int func_8008AE30(int, int);
void func_800738D4(int, Vector *, int, Tint *, int);
void func_8003BADC(int, int);
unsigned int func_80086C84(void);
void func_80053790(int, int, int);
void func_8001B094(int);
void func_8002CA3C(Crate *, int, void *, void *);
void func_8002CBEC(Crate *, int, void *);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

static inline void smash(Crate *c, int angle) {
    Tint tint;

    if (c->state != 3) {
        if (c->model != 0) {
            tint = D_800BD92C;
            func_800738D4(c->model, &c->pos, angle, &tint, 100);
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
    }
}

void func_8002CD34(Crate *c, int msg, unsigned int event, void *data, void *out) {
    Crate *self = c;

    switch (event) {
    case 0:
        func_8002CA3C(c, msg, data, out);
        break;
    case 5:
        if (*(int *)data == 0 && c->state == 0) {
            ((Query *)out)->valid = 1;
            ((Query *)out)->x = c->target->pos.x;
            ((Query *)out)->z = c->target->pos.z;
        }
        break;
    case 6:
        if (c->state == 0) {
            smash(self, (func_8008AE30(c->target->pos.x - ((Hit2 *)data)->x, c->target->pos.z - ((Hit2 *)data)->z) &
                         0xFFF)
                            << 4);
        }
        break;
    case 3:
        func_8002CBEC(c, msg, data);
        break;
    }
}

typedef struct {
    char pad0[8];
    int pos[3];
    char pad14[8];
    unsigned int state;
    char pad20[4];
    int start;
    int param;
    unsigned short sound;
} Effect;

extern int D_800D2FE0;
extern void func_8001B094(int);
extern void func_800235E0(int *, int, int, int, int);

void func_80028314(Effect *e, int *done) {
    switch (e->state) {
    case 1:
        break;
    case 0:
        if (D_800D2FE0 - e->start >= 46) {
            e->state = 1;
        }
        break;
    case 5:
        func_8001B094(e->sound);
        *done = 1;
        break;
    case 2:
        if (D_800D2FE0 - e->start >= 16) {
            *done = 1;
            func_800235E0(e->pos, 108, 819, e->param, 0xE49D0A);
        }
        break;
    }
}

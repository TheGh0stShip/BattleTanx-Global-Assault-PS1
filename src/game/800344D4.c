typedef struct { int x, y, z; } Vector;
typedef struct { int pad[2]; Vector pos; int end_time; unsigned int chance; } Spawner;
extern int D_800D2FE0;
unsigned int func_80086C84(void);
void func_80034544(Vector *);

void func_800344D4(Spawner *s, int *done) {
    int now = D_800D2FE0;

    if (s->end_time < now) {
        *done = 1;
        return;
    }
    while ((func_80086C84() & 0xFFF) < s->chance) {
        func_80034544(&s->pos);
    }
}

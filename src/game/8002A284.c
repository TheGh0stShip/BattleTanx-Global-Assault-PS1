typedef struct {
    char pad0[8];
    int pos[3];
    unsigned short angle;
    char pad16[2];
    int kind;
    int done;
} Effect;

extern int D_800A4754[];
extern int D_800C60D0;
extern void func_8006A158(int, int *, int, int, int);

void func_8002A284(Effect *e) {
    if (e->done == 0 && e->kind != 0) {
        func_8006A158(D_800A4754[e->kind], e->pos, 0, e->angle, 0);
        if (D_800C60D0 != 7) {
            e->angle += 0x600;
        }
    }
}

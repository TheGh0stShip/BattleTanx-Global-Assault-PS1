typedef struct { int x, y, z; } Vector;
typedef struct { char pad[72]; int wreck_model; char rest[0xD0 - 76]; } VehicleInfo;
typedef struct { int pad[2]; int vehicle; Vector pos; unsigned short angle; unsigned short sound; char pad2[8]; int hp; } Wreck;
extern VehicleInfo D_800A4EF4[];
extern int D_800D2E14[];
void func_80035948(int, Vector *, int, int, int, int, int, int);
void func_8001B094(int);

void func_800377D0(Wreck *w, int *done) {
    if (w->hp <= 0) {
        func_80035948(D_800D2E14[D_800A4EF4[w->vehicle].wreck_model], &w->pos, w->angle, 0, 0, 0, 0, 0);
        func_8001B094(w->sound);
        *done = 1;
    }
}

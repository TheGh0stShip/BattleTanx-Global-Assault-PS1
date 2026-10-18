typedef struct { int x, y, z; } Vector;
typedef struct { char pad[68]; int model; char rest[0xD0 - 72]; } VehicleInfo;
typedef struct { int pad[2]; int vehicle; Vector pos; unsigned short angle; char pad2[7]; unsigned char flag; } Fx;
extern VehicleInfo D_800A4EF4[];
extern int D_800D2E14[];
void func_80069494(int, Vector *, int, int, int, int);

void func_80037878(Fx *fx) {
    func_80069494(D_800D2E14[D_800A4EF4[fx->vehicle].model], &fx->pos, 0, fx->angle, 0, fx->flag);
}

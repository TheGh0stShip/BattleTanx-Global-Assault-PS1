typedef struct Spot {
    short x;
    short y;
    char pad[88];
} Spot;

typedef struct Area {
    Spot spots[3];
    char pad[20];
} Area;

extern int D_800A48B0;
extern int D_800A48AC;
extern Area D_800DDB9C[];
extern char D_800AE9E0[];
extern void func_8007FCE8(void *, int, int);
extern void func_8007FA74(int);

void func_800757F0(void) {
    Area *a = &D_800DDB9C[D_800A48B0];
    Spot *s = &a->spots[D_800A48AC];
    func_8007FCE8(D_800AE9E0, s->x, s->y);
    func_8007FA74(0);
}

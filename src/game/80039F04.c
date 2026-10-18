typedef struct { int x; int y; int z; } Vector;
typedef struct { short x; short y; short z; short pad; } SVector;
typedef struct { short m[3][3]; short pad; int t[3]; } Matrix;
typedef struct { char pad[2]; short mode; char pad1[4]; Vector pos; char pad2[0x70 - 0x14]; Matrix rot; char pad3[156 - 0x90]; } View;
typedef struct { unsigned char f0; unsigned char current; char pad[2]; View views[1]; } ViewSet;
extern ViewSet D_800D3034;
extern SVector D_800D5B38;
extern int D_800A489C;
extern int D_800A48A0;
extern int D_800A48A4;
extern SVector D_800D5B60[4];
extern SVector D_800D5B0C[4];
extern SVector D_800D5AA4[4];
extern void func_8008B844(Matrix *);
extern void func_8003940C(int, SVector *);
extern void func_800399D0(SVector *, int);

static inline int round_int(int a, int b)
{
    int r;
    int v;

    v = a - b;
    if (v >= 0) {
        r = v + 2048;
        if (r >= 0) {
            return r >> 12;
        }
        return -(-r >> 12);
    }
    r = v - 2048;
    if (r >= 0) {
        return r >> 12;
    }
    return -((2048 - v) >> 12);
}

static inline int round_value(int v)
{
    int r;
    if (v >= 0) {
        r = v + 2048;
        if (r >= 0) {
            return r >> 12;
        }
        return -(-r >> 12);
    }
    r = v - 2048;
    if (r >= 0) {
        return r >> 12;
    }
    return -((2048 - v) >> 12);
}

void func_80039F04(void)
{
    Matrix m;

    D_800D5B38.x = round_int(0, D_800D3034.views[D_800D3034.current].pos.x);
    D_800D5B38.y = round_int(0, D_800D3034.views[D_800D3034.current].pos.y);
    D_800D5B38.z = round_value(D_800D3034.views[D_800D3034.current].pos.z);
    m = D_800D3034.views[D_800D3034.current].rot;
    D_800A489C = D_800D5B38.x;
    D_800A48A0 = D_800D5B38.y;
    D_800A48A4 = D_800D5B38.z;
    m.t[0] = 0;
    m.t[1] = 0;
    m.t[2] = 0;
    func_8008B844(&m);
    func_8003940C(D_800D3034.views[D_800D3034.current].mode, &D_800D5B38);
    D_800D5B60[0].x = D_800D5B0C[0].x;
    D_800D5B60[1].x = D_800D5B0C[1].x;
    D_800D5B60[2].x = D_800D5AA4[1].x;
    D_800D5B60[3].x = D_800D5AA4[0].x;
    D_800D5B60[0].y = D_800D5B0C[0].y;
    D_800D5B60[1].y = D_800D5B0C[1].y;
    D_800D5B60[2].y = D_800D5AA4[1].y;
    D_800D5B60[3].y = D_800D5AA4[0].y;
    func_800399D0(D_800D5B60, 1);
    D_800D5B60[0].x = D_800D5B0C[2].x;
    D_800D5B60[1].x = D_800D5B0C[3].x;
    D_800D5B60[2].x = D_800D5AA4[3].x;
    D_800D5B60[3].x = D_800D5AA4[2].x;
    D_800D5B60[0].y = D_800D5B0C[2].y;
    D_800D5B60[1].y = D_800D5B0C[3].y;
    D_800D5B60[2].y = D_800D5AA4[3].y;
    D_800D5B60[3].y = D_800D5AA4[2].y;
    func_800399D0(D_800D5B60, 2);
}
